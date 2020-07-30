// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElevatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UElevatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	class UGameManager* GM;
	class AGameHUD* UI;
	class AProjectIdleCharacter* Player;

	UPROPERTY(BlueprintReadWrite) class AElevator* Elevator;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Btn_Floor_1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Btn_Floor_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Btn_Floor_3;

private:
	virtual void NativeConstruct() override;

	UFUNCTION() void MoveToFloorOne();
	UFUNCTION() void MoveToFloorTwo();
    UFUNCTION() void MoveToFloorThree();

};
