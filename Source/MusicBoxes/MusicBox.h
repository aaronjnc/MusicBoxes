// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicBoxPiece.h"
#include "PutTogetherPuzzle.h"
#include "MusicBox.generated.h"

UCLASS()
class MUSICBOXES_API AMusicBox : public APutTogetherPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool AddPiece(APickup *Pickup) override;
	
	virtual void FinishPuzzle() override;

private:

	UPROPERTY(EditAnywhere, Category = "Puzzle")
		TArray<EPieceType> PieceTypes;

	UPROPERTY()
		TMap<EPieceType, USceneComponent *> MusicPieceMap;
};
