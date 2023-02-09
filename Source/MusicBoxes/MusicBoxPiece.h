// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "MusicBoxPiece.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EPieceType : uint8
{
	Santa,
	Crank,
	Gears,
};

UCLASS()
class MUSICBOXES_API AMusicBoxPiece : public APickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicBoxPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetPieceType();

	EPieceType GetPieceTypeEnum();

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent *BoxColliderComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent *MeshComponent;

	UPROPERTY(EditAnywhere)
		EPieceType PieceType;
};