// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employees/Employee.h"
#include "GameManager.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

UCLASS()
class PROJECTIDLE_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UGameSave();
	UGameManager* GM;
	UPROPERTY(EditAnywhere) bool IdeaInProduction;
	UPROPERTY(EditAnywhere)	bool AutoManaging;
	UPROPERTY(EditAnywhere) int NumEmployees;
	UPROPERTY(EditAnywhere) FDateTime SavedTime;
	UPROPERTY(EditAnywhere) FVector Saved_PlayerLocation;

	UPROPERTY(EditAnywhere) CRating CompanyRating;
	UPROPERTY(EditAnywhere) int CompanyLevel;
	UPROPERTY(EditAnywhere) float CurrentExp;
	UPROPERTY(EditAnywhere) float MaxExp;


	UPROPERTY(EditAnywhere) int Saved_Money;
	UPROPERTY(EditAnywhere) int FloorMaterialID;
	UPROPERTY(EditAnywhere) int WallMaterialID;
	UPROPERTY(EditAnywhere) TArray<class AItem*> InventoryList;
	UPROPERTY(EditAnywhere) TArray<class AWorkstation*> WorkstationList;
	UPROPERTY(EditAnywhere) bool IsFloorUpgraded;
    TArray<class Idea*> IdeaList;


public:
	// void SaveEmployeeRecords(FArchive Ar); Method 1
	void ClearLists();
};
