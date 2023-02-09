// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	Star,
	Gift1,
	Gift2,
	Gift3,
	Stocking1,
	Stocking2,
	Stocking3,
	Cookies,
	MusicBox,
};

UCLASS()
class MUSICBOXES_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EPickupType GetPickupType();

private:

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent *PickupMesh;

	UPROPERTY(EditAnywhere, Category = "Puzzle Parts")
		EPickupType PickupType;

};
