// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "MoneyWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void UpdateMoney(int32 Value);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MoneyWidgetClass;

private:
	UMoneyWidget* MoneyWidget;
};
