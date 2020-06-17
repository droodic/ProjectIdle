// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UItemButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget)) class UButton* Item_Btn;

	UPROPERTY(meta = (BindWidget)) class UImage* Item_I;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemName_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* ItemPrice_T;

	UPROPERTY(EditAnywhere) TSubclassOf<class AItem> BPItem;

private:
	int ItemID;

	class AItem* Item;

private:
	void NativeConstruct() override;
	
	UFUNCTION() void OnClicked();

};
