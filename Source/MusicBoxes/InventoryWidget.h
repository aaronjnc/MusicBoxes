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

	void PickupItem(int i);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<UImage *> ImageComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<UTexture2D *> FoundImages;
	
private:

	UPROPERTY(EditAnywhere, Category = "Items")
		UTexture2D *HiddenImage;
	
};
