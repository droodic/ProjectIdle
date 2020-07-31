// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
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
	class UGameManager* GM;

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MoneyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> EmployeeSheetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> WorkstationClass;

	UPROPERTY() class UEmployeeSheetWidget* EmpSheetWidget;
	//class UCeoDepMenuWidget* OfficeDepMenuWidget;

	class UMoneyWidget* MoneyWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio") class USoundCue* NotificationSound;
	UAudioComponent* NotificationAudio;

private:
	//UWorkstationUpgradeWidget* WorkstationWidget;

public:
	void ShowEmployeeSheet(class AEmployee* employee);
	void RefreshEmployeeSheet(class AEmployee* employee);
	void ShowStationUpgrade(class AWorkstation* station);
	void CloseEmployeeSheet();
	void ShowWidget(UUserWidget* Widgetc, TSubclassOf<UUserWidget> WidgetClass);
	void PlayNotification();
};
