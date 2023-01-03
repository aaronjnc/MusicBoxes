// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicBoxPiece.h"
#include "Components/BoxComponent.h"

// Sets default values
AMusicBoxPiece::AMusicBoxPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxColliderComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMusicBoxPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicBoxPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPieceType AMusicBoxPiece::GetPieceType()
{
	return PieceType;
}


