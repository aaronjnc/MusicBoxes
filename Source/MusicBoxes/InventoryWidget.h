// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UImage;
UCLASS()
class MUSICBOXES_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

private:

	UPROPERTY(EditAnywhere, Category = "Items")
	TArray<UImage *> ImageComponents;

	UPROPERTY(EditAnywhere, Category = "Items")
		TArray<UTexture2D *> FoundImages;

	UPROPERTY(EditAnywhere, Category = "Items")
		UTexture2D *HiddenImage;
	
};
