// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PutTogetherPuzzle.h"
#include "ConnectedPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class MUSICBOXES_API AConnectedPuzzle : public APutTogetherPuzzle
{
	GENERATED_BODY()
	
public:

	virtual void FinishPuzzle() override;

	bool IsFinished();

private:

	UPROPERTY(EditAnywhere, Category = "Puzzle")
		AConnectedPuzzle *PartnerPuzzle;
	
};
