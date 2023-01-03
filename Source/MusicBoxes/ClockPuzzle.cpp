// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockPuzzle.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/StaticMeshComponent.h"

AClockPuzzle::AClockPuzzle() : AInteractablePuzzle()
{
	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockMesh"));
	ClockMesh->SetupAttachment(RootComponent);

	HourHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHandMesh"));
	HourHandMesh->SetupAttachment(ClockMesh);

	MinuteHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHandMesh"));
	MinuteHandMesh->SetupAttachment(ClockMesh);
}


void AClockPuzzle::Interact()
{
	Super::Interact();
	PlayerController->bShowMouseCursor = true;
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ClockMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			//Clicking
			EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AClockPuzzle::ClickEvent);
			BindingNum = EnhancedInputComponent->GetNumActionBindings() - 1;

			EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &AClockPuzzle::ChangeTime);
		}
	}
}

void AClockPuzzle::ClickEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	FVector StartLocation;
	FVector Dir;
	PlayerController->DeprojectMousePositionToWorld(StartLocation, Dir);

	FVector End = StartLocation + Dir * 1000;

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, End, ECollisionChannel::ECC_Visibility))
	{
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (HitComp == HourHandMesh)
		{
			HourHandMesh->SetMaterial(0, HandSelected);
			MinuteHandMesh->SetMaterial(0, HandUnselected);
			PossessedHand = HourHandMesh;
		}
		else if (HitComp == MinuteHandMesh)
		{
			MinuteHandMesh->SetMaterial(0, HandSelected);
			HourHandMesh->SetMaterial(0, HandUnselected);
			PossessedHand = MinuteHandMesh;
		}
		else
		{
			MinuteHandMesh->SetMaterial(0, HandUnselected);
			HourHandMesh->SetMaterial(0, HandUnselected);
			PossessedHand = nullptr;
		}
	}
	else
	{
		PossessedHand = nullptr;
	}
}

void AClockPuzzle::ChangeTime(const FInputActionValue& Value)
{
	float Dir = Value.Get<float>();

	if (PossessedHand != nullptr)
	{
		const FRotator Rotation = FRotator(0, 0, Dir);
		PossessedHand->AddRelativeRotation(Rotation);
		if (PossessedHand == HourHandMesh)
		{
			CurrentHourAngle += Dir;
			CurrentHourAngle = (int)CurrentHourAngle % 360;
			if (CurrentHourAngle < 0)
			{
				CurrentHourAngle += 360;
			}
		}
		else
		{
			CurrentMinuteAngle += (int)Dir;
			CurrentMinuteAngle = (int)CurrentMinuteAngle % 360;
			if (CurrentMinuteAngle < 0)
			{
				CurrentMinuteAngle += 360;
			}
		}
		float HourAngleDiff = FMath::Abs(CurrentHourAngle - HourAngle);
		float MinuteAngleDiff = FMath::Abs(CurrentMinuteAngle - MinuteAngle);
		if (HourAngleDiff < 5 && MinuteAngleDiff < 5)
		{
			UE_LOG(LogTemp, Warning, TEXT("Puzzle Complete"));
		}
	}
}

void AClockPuzzle::LeavePuzzle()
{
	PlayerController->bShowMouseCursor = false;
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(ClockMappingContext);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			//Remove Input
			EnhancedInputComponent->RemoveActionBinding(BindingNum);
		}
	}
}