// Fill out your copyright notice in the Description page of Project Settings.


#include "CheatMode.h"
#include "GameManager.h"
#include "ProjectIdleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStaticsTypes.h"


void UCheatMode::Cheat_AllCheatOn()
{
	Cheat_MaxMoney();
	//Cheat_MaxSpeed();
	Cheat_FastCompile();
}



void UCheatMode::Cheat_MaxMoney()
{
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Money = INT32_MAX;
}

//void UCheatMode::Cheat_MaxSpeed()
//{
//	GM = GetWorld()->GetGameInstance<UGameManager>();
//	GM->Character->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
//	for (int i = 0; i < GM->EmployeeList.Num(); i++)
//	{
//		GM->EmployeeList[i]->GetCharacterMovement()->MaxWalkSpeed = Speed;
//	}
//}

void UCheatMode::Cheat_FastCompile()
{
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->CheatSpeedRate = 200.0f;
	for (int i = 0; i < GM->WorkstationList.Num(); i++)
	{
		GM->WorkstationList[i]->CompileModifier = 50;
		GM->WorkstationList[i]->CurrentCompileLoad = 1;
	}
}

