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
	class UGameManager* GameManager;
	AWorkstation* CurrentStation;

	AItem* Item;
	UPROPERTY(meta = (BindWidget)) class UButton* Item_Btn;
	UPROPERTY(meta = (BindWidget)) class UImage* Item_I;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemName_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemCount_T;

public:
	void NativeConstruct() override;
	UFUNCTION() void OnClicked();
};
