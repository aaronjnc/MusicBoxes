// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractablePuzzle.h"
#include "InputActionValue.h"
#include "ClockPuzzle.generated.h"

class UStaticMeshComponent;

UCLASS()
class MUSICBOXES_API AClockPuzzle : public AInteractablePuzzle
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	AClockPuzzle();

	void Interact() override;

	void LeavePuzzle() override;

private:

	UPROPERTY(EditAnywhere, Category = "Clock Components")
		UStaticMeshComponent* ClockMesh;
	UPROPERTY(EditAnywhere, Category = "Clock Components")
		UStaticMeshComponent* HourHandMesh;
	UPROPERTY(EditAnywhere, Category = "Clock Components")
		UStaticMeshComponent* MinuteHandMesh;
	UPROPERTY(EditAnywhere, Category = "Clock Components")
		UStaticMeshComponent* RemovableGlass;

	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
		UMaterial* HandSelected;
	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
		UMaterial* HandUnselected;

	UPROPERTY(EditAnywhere, Category = "Input")
		class UInputMappingContext* ClockMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* ClickAction;
	UPROPERTY(EditAnywhere, Category = "Input")
		UInputAction* ScrollAction;
	
	UPROPERTY()
		int BindingNum = 0;
	UPROPERTY()
		UStaticMeshComponent* PossessedHand;
		
	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
	    float HourAngle;
	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
		float MinuteAngle;
	UPROPERTY()
		float CurrentHourAngle = 0;
	UPROPERTY()
		float CurrentMinuteAngle = 0;
	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
		FVector ClockCenter;
	UPROPERTY()
		float MoveDist;
	UPROPERTY()
		float YDirection = 1;
	UPROPERTY()
		float ZDirection = 1;

	UPROPERTY()
		float ZModifier;
	
	void ClickEvent();

	void ChangeTime(const FInputActionValue& Value);
};
