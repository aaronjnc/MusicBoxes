// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Scene.h"
#include "GameFramework/Actor.h"
#include "Fridge.generated.h"

UCLASS()
class MUSICBOXES_API AFridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact();

private:

	UPROPERTY(VisibleAnywhere, Category = "Open")
		USceneComponent *FridgeDoor;

	UPROPERTY(EditAnywhere, Category = "Open")
		FVector OpenPosition;

	UPROPERTY(EditAnywhere, Category = "Open")
		FRotator OpenRotation;

	UPROPERTY()
		bool IsOpen = false;

};
