// Fill out your copyright notice in the Description page of Project Settings.


#include "PutTogetherPuzzle.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
APutTogetherPuzzle::APutTogetherPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	PuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	PuzzleMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APutTogetherPuzzle::BeginPlay()
{
	Super::BeginPlay();
	PuzzleMesh->GetChildrenComponents(true, StaticMeshes);
	for (int i = 0; i < PuzzleTypes.Num() && i < StaticMeshes.Num(); i++)
	{
		StaticMeshes[i]->SetVisibility(false);
		PuzzleMap.Add(PuzzleTypes[i], StaticMeshes[i]);
	}
	MeshesLeft = StaticMeshes.Num();
}

// Called every frame
void APutTogetherPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APutTogetherPuzzle::AddPiece(APickup *Pickup)
{
	EPickupType PickupType = Pickup->GetPickupType();
	if (PuzzleMap.Contains(PickupType))
	{
		PuzzleMap[PickupType]->SetVisibility(true);
		MeshesLeft--;
		if (MeshesLeft == 0)
		{
			FinishPuzzle();
		}
		return true;
	}
	return false;
}

void APutTogetherPuzzle::FinishPuzzle()
{
	for (AActor *A : ActorsToAppear)
	{
		A->SetActorHiddenInGame(false);
	}
}
