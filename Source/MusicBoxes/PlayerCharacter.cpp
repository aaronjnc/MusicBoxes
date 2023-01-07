// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractablePuzzle.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MusicBoxPiece.h"
#include "Pickup.h"
#include "PutTogetherPuzzle.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	PlayerMesh = GetMesh();
	PlayerMesh->SetOnlyOwnerSee(true);
	PlayerMesh->bCastDynamicShadow = false;
	PlayerMesh->CastShadow = false;
	PlayerMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidget);
	InventoryWidgetInstance->AddToViewport();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Pickup)
	{
		PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + GetActorForwardVector() * 100, GetActorRotation());
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact()
{
	if (!bPossessing)
	{
		FVector Location;
		FRotator Rotation;
		Controller->GetPlayerViewPoint(Location, Rotation);

		FVector End = Location + Rotation.Vector() * MaxRange;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_Visibility))
		{
			if (Hit.GetActor()->IsA<AInteractablePuzzle>())
			{
				Possessed = Cast<AInteractablePuzzle>(Hit.GetActor());
				if (Possessed != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Interact"));
					FirstPersonCameraComponent->SetActive(false);
					Possessed->Interact();
					bPossessing = true;
				}
				Subsystem->RemoveMappingContext(DefaultMappingContext);
			}
			else if (Hit.GetActor()->IsA<APickup>())
			{
				if (Pickup)
					return;
				Pickup = Cast<APickup>(Hit.GetActor());
				UPrimitiveComponent *HitComponent = Hit.GetComponent();
				HitComponent->SetSimulatePhysics(true);
				HitComponent->WakeAllRigidBodies();
				PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Hit.ImpactPoint, GetActorRotation());
			}
			else if (Hit.GetActor()->IsA<APutTogetherPuzzle>())
			{
				if (!Pickup)
					return;
				APutTogetherPuzzle *Puzzle = Cast<APutTogetherPuzzle>(Hit.GetActor());
				if (Puzzle->AddPiece(Pickup))
				{
					if (Pickup->GetPickupType() == EPickupType::MusicBox)
					{
						AMusicBoxPiece *Piece = Cast<AMusicBoxPiece>(Pickup);
						InventoryWidgetInstance->PickupItem(Piece->GetPieceType());
					}
					PhysicsHandle->ReleaseComponent();
					Pickup->Destroy();
					Pickup = nullptr;
				}
			}
		}
	}
	else
	{
		PlayerController->SetViewTargetWithBlend(this, 1.f);
		Possessed->LeavePuzzle();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		bPossessing = false;
	}
}


