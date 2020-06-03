// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "Widgets/MoneyWidget.h"
#include "ProjectIdle/Widgets/EmployeeSheetWidget.h"
//#include "ProjectIdle/Widgets/WorkstationUpgradeWidget.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MoneyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> EmployeeSheetClass;

	//UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	//	TSubclassOf<UUserWidget> WorkstationClass;

	//class UCeoDepMenuWidget* OfficeDepMenuWidget;

private:
	UMoneyWidget* MoneyWidget;
	UEmployeeSheetWidget* EmpSheetWidget;
	//UWorkstationUpgradeWidget* WorkstationWidget;

public:
	void ShowEmployeeSheet(class AEmployee* employee);
	void RefreshEmployeeSheet(class AEmployee* employee);
	//void ShowStationUpgrade(class AWorkstation* station);

	void ShowWidget(UUserWidget* Widgetc, TSubclassOf<UUserWidget> WidgetClass);
};
