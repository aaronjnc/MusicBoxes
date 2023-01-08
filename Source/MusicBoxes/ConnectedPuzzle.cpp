// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectedPuzzle.h"

void AConnectedPuzzle::FinishPuzzle()
{
	if (PartnerPuzzle->IsFinished())
	{
		Super::FinishPuzzle();
	}
}

bool AConnectedPuzzle::IsFinished()
{
	return PuzzlePiecesLeft == 0;
}
