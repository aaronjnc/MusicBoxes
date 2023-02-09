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
	TArray<FString> TypeNames;
	for (EPickupType Pickup : PuzzleTypes)
	{
		FString EnumName;
		FString PuzzleName;
		UEnum::GetValueAsName(Pickup).ToString().Split(TEXT("::"), &EnumName, &PuzzleName);
		TypeNames.Add(PuzzleName);
	}
	for (int i = 0; i < StaticMeshes.Num(); i++)
	{
		if (TypeNames.Contains(StaticMeshes[i]->GetName()))
		{
			int index = TypeNames.Find(StaticMeshes[i]->GetName());
			PuzzleMap.Add(PuzzleTypes[index], StaticMeshes[i]);
		}
		StaticMeshes[i]->SetVisibility(false);
	}
	MeshesLeft = StaticMeshes.Num();
	PuzzlePiecesLeft = PuzzleTypes.Num();
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
		PuzzlePiecesLeft--;
		if (PuzzlePiecesLeft == 0)
		{
			if (MeshesLeft != 0)
			{
				for (USceneComponent *M : StaticMeshes)
				{
					M->SetVisibility(true);
				}
			}
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
