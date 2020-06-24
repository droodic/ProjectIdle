// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTIDLE_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UGameManager* GameManager;
	class AOfficeDepartment* OfficeDepartment;
	class AItem* ItemRef;
	//AItem* CurrentItem;

	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab1;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab2;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab3;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab4;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* CheckoutItems_WB;
	UPROPERTY(meta = (BindWidget)) class UCanvasPanel* DescriptionPanel;

	UPROPERTY(meta = (BindWidget)) class UButton* Buy_Btn;
	UPROPERTY(meta = (BindWidget)) class UButton* ShopReturn_Btn;

	UPROPERTY(meta = (BindWidget)) class UTextBlock* Money_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* TotalMoney_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* NotEnoughMoney_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* CheckoutCount_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* Description_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* DescriptionStats_T;


	UPROPERTY(EditAnywhere) TSubclassOf<class UUserWidget> ItemButtonClass;

private:
	TArray<class UItemButton*> CheckList;
	FTimerHandle TimerHandle;

	int CheckoutCount = 0;
	int Total = 0;

public:
	UFUNCTION() void Return();
	UFUNCTION() void Buy();

	void AddItemToCheckout(class AItem* item);
	void RemoveItemFromCheckout(int ItemID);

private:
	void NativeConstruct() override;
	void RemoveNotEnoughMoney();
};
