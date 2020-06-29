// Fill out your copyright notice in the Description page of Project Settings.


#include "CheatMode.h"
#include "GameManager.h"
#include "ProjectIdleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStaticsTypes.h"

void UCheatMode::MaxMoney()
{
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Money = INT32_MAX;
}

void UCheatMode::MaxSpeed()
{
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Character->IdleMaxSpeed();
}

