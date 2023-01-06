// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "PutTogetherPuzzle.generated.h"

UCLASS()
class MUSICBOXES_API APutTogetherPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APutTogetherPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AddPiece(EPickupType PickupType);

	void FinishPuzzle();

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent *PuzzleMesh;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
		TArray<EPickupType> PuzzleTypes;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		TArray<USceneComponent *> StaticMeshes;
	
	UPROPERTY()
		TMap<EPickupType, USceneComponent *> PuzzleMap;

	UPROPERTY()
		int MeshesLeft;
	
};
