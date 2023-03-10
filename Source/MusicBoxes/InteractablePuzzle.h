// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InteractablePuzzle.generated.h"

class UCameraComponent;
class USceneComponent;

UCLASS()
class MUSICBOXES_API AInteractablePuzzle : public APawn
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* PuzzleViewCamera;
	
public:	
	// Sets default values for this actor's properties
	AInteractablePuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();

	virtual void LeavePuzzle();

protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* ClockMappingContext;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
};
