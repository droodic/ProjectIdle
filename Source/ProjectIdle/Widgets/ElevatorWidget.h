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

private:

	virtual void NativeConstruct() override;
};
