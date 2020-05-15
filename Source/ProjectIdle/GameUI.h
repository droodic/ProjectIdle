// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UGameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		class AProjectIdleCharacter* player;
};
