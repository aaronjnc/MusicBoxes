// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicBox.h"

// Sets default values
AMusicBox::AMusicBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMusicBox::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < PieceTypes.Num() && i < StaticMeshes.Num(); i++)
	{
		MusicPieceMap.Add(PieceTypes[i], StaticMeshes[i]);
	}
	MeshesLeft++;
}

// Called every frame
void AMusicBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMusicBox::AddPiece(APickup* Pickup)
{
	if (Pickup->GetPickupType() == EPickupType::MusicBox)
	{
		AMusicBoxPiece *MusicBoxPiece = Cast<AMusicBoxPiece>(Pickup);
		if (MusicBoxPiece)
		{
			if (MusicBoxPiece->GetPieceTypeEnum() != EPieceType::Gears)
				MusicPieceMap[MusicBoxPiece->GetPieceTypeEnum()]->SetVisibility(true);
			MeshesLeft--;
			if (MeshesLeft == 0)
			{
				FinishPuzzle();
			}
			return true;
		}
		return false;
	}
	return false;
}

void AMusicBox::FinishPuzzle()
{
	UE_LOG(LogTemp, Warning, TEXT("Play Music"));
}

