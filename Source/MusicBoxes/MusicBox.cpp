// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicBox.h"

// Sets default values
AMusicBox::AMusicBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMusicBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

