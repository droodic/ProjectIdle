// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "GameSave.h"
#include "MeetingDepartment.h"



UGameManager::UGameManager() {
	Money = 180000; //temp
}

void UGameManager::Init()
{

}

void UGameManager::SaveGame()
{
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	
	//Save Var
	SaveGameInstance->Saved_Money = Money;



	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);
}

void UGameManager::LoadGame()
{
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	SaveGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));

	//Unload vars
	Money = SaveGameInstance->Saved_Money;

}