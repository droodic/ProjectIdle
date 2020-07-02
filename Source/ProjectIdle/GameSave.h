// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employees/Employee.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

UCLASS()
class PROJECTIDLE_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UGameSave();
	UGameManager* GM;
	int NumEmployees;
	bool AutoManaging;
	bool IdeaInProduction;
	UPROPERTY(EditAnywhere) FDateTime SavedTime;
	UPROPERTY(EditAnywhere) FVector Saved_PlayerLocation;
	UPROPERTY(EditAnywhere) int Saved_Money;
	UPROPERTY(EditAnywhere) TArray<class AItem*> InventoryList;
	UPROPERTY(EditAnywhere) TArray<class AWorkstation*> WorkstationList;
    TArray<class Idea*> IdeaList;

public:
	// void SaveEmployeeRecords(FArchive Ar); Method 1
	void ClearLists();
};
