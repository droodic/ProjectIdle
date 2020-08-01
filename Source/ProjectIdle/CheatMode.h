// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CheatMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UCheatMode : public UCheatManager
{
	GENERATED_BODY()
	

public:
	class UGameManager* GM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed") float Speed = 1500.0f;

	UFUNCTION(Exec) void Cheat_AllCheatOn();
	UFUNCTION(Exec) void Cheat_MaxMoney();
	//UFUNCTION(Exec) void Cheat_MaxSpeed();
	UFUNCTION(Exec) void Cheat_FastCompile();


};
