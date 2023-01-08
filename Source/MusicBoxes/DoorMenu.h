// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorMenu.generated.h"

UCLASS()
class MUSICBOXES_API ADoorMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PauseGame();

	void UnPauseGame();
	
private:

    UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidget;

	UPROPERTY()
	UUserWidget *MenuWidgetInstance;

};
