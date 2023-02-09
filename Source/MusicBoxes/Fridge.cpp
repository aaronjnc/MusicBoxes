// Fill out your copyright notice in the Description page of Project Settings.


#include "Fridge.h"

// Sets default values
AFridge::AFridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	
	FridgeDoor = CreateDefaultSubobject<USceneComponent>(TEXT("Fridge Door"));
	FridgeDoor->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFridge::Interact()
{
	if (!IsOpen)
	{
		FridgeDoor->SetRelativeLocation(OpenPosition);
		FridgeDoor->SetRelativeRotation(OpenRotation);
		IsOpen = true;
	}
	else
	{
		FridgeDoor->SetRelativeLocation(FVector::Zero());
		FridgeDoor->SetRelativeRotation(FRotator::ZeroRotator);
		IsOpen = false;
	}
}

