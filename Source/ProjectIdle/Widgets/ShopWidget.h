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
	class AOfficeDepartment* OfficeDepartment;


	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab1;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab2;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab3;
	UPROPERTY(meta = (BindWidget)) class UWrapBox* Tab4;

	UPROPERTY(meta = (BindWidget)) class UButton* ShopReturn_Btn;

public:
	UFUNCTION() void Return();

private:
	void NativeConstruct() override;
};
