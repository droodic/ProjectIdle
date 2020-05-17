// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MoneyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMoneyWidget(const FObjectInitializer& ObjectInitializer);


	virtual void NativeConstruct() override;

	void UpdateMoney(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TotalMoney;
};
