// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InteractablePuzzle.h"
#include "InventoryWidget.h"
#include "Pickup.h"
#include "PlayerCharacter.generated.h"

class USkeletalBodySetup;
class UCameraComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UUserWidget;
class UPhysicsHandleComponent;

UCLASS()
class MUSICBOXES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsHandleComponent *PhysicsHandle;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact();

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY()
	bool bPossessing = false;

	UPROPERTY()
	AInteractablePuzzle* Possessed;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float MaxRange;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InventoryWidget;

	UPROPERTY()
		UInventoryWidget *InventoryWidgetInstance;

	UPROPERTY()
		APickup *Pickup;
};