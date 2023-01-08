// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorMenu.h"

#include "Blueprint/UserWidget.h"

// Sets default values
ADoorMenu::ADoorMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorMenu::BeginPlay()
{
	Super::BeginPlay();

	MenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MenuWidget);
	MenuWidgetInstance->AddToViewport(1);
	MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	
}

// Called every frame
void ADoorMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorMenu::PauseGame()
{
	MenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
}

void ADoorMenu::UnPauseGame()
{
	MenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
}

