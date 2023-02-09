// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePuzzle.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractablePuzzle::AInteractablePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PuzzleViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PuzzleCamera"));
	PuzzleViewCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractablePuzzle::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void AInteractablePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractablePuzzle::Interact()
{
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ClockMappingContext, 1);
		}
	}
	PlayerController->SetViewTargetWithBlend(this, 1.f);
}

void AInteractablePuzzle::LeavePuzzle()
{
	
}