// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UGameSave();

	UPROPERTY(EditAnywhere) FVector Saved_PlayerLocation;
	UPROPERTY(EditAnywhere) int Saved_Money;
	
};
