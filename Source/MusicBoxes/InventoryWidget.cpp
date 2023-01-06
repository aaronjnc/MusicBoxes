// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	for (UImage *I : ImageComponents)
	{
		if (I)
			I->SetBrushFromTexture(HiddenImage);
	}
}

void UInventoryWidget::PickupItem(int i)
{
	if (ImageComponents[i] && FoundImages[i])
		ImageComponents[i]->SetBrushFromTexture(FoundImages[i]);
}
