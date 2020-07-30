// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UInventoryButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryButton(const FObjectInitializer& ObjectInitializer);
	
	class AWorkstation* CurrentStation;

	class AItem* Item;
	UPROPERTY(meta = (BindWidget)) class UButton* Item_Btn;
	UPROPERTY(meta = (BindWidget)) class UImage* Item_I;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemName_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemCount_T;

	UPROPERTY(EditAnywhere) TSubclassOf<class AItem> ItemBP;

private:
	class UGameManager* GameManager;

private:
	void NativeConstruct() override;
	void NativePreConstruct() override;

	UFUNCTION() void OnClicked();
};
