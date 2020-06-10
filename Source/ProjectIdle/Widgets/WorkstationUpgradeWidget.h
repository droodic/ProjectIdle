// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "ProjectIdle/Workstation.h"
#include "WorkstationUpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UWorkstationUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	class AWorkstation* Station;
	class UGameManager* GM;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* UpgradeMonitor_Btn;

	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void Monitor();

private:
	virtual void NativeConstruct() override;
	
};
