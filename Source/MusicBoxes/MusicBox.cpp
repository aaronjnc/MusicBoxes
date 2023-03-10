// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicBox.h"
#include "Components/AudioComponent.h"


// Sets default values
AMusicBox::AMusicBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Music Component"));
	AudioComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMusicBox::BeginPlay()
{
	Super::BeginPlay();
	TArray<FString> TypeNames;
	for (EPieceType Pickup : PieceTypes)
	{
		FString EnumName;
		FString PuzzleName;
		UEnum::GetValueAsName(Pickup).ToString().Split(TEXT("::"), &EnumName, &PuzzleName);
		TypeNames.Add(PuzzleName);
		UE_LOG(LogTemp, Warning, TEXT("Type: %s"), *PuzzleName);
	}
	for (int i = 0; i < StaticMeshes.Num(); i++)
	{
		if (TypeNames.Contains(StaticMeshes[i]->GetName()))
		{
			int index = TypeNames.Find(StaticMeshes[i]->GetName());
			MusicPieceMap.Add(PieceTypes[index], StaticMeshes[i]);
		}
		StaticMeshes[i]->SetVisibility(false);
	}
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
			PuzzlePiecesLeft--;
			if (PuzzlePiecesLeft == 0)
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
	AudioComponent->Play();
	UE_LOG(LogTemp, Warning, TEXT("Play Music"));
}

