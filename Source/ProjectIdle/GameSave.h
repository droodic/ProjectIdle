// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employees/Employee.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

/**
 * 
 */
/*
Method 0
USTRUCT()
struct FActorSaveInfo {
	GENERATED_USTRUCT_BODY()

	FString ActorClass;
	FName ActorName;
	FTransform ActorTransform;
	TArray<uint8> ActorData;

	friend FArchive& operator<<(FArchive& Ar, FActorSaveInfo& ActorData)
	{
		Ar << ActorData.ActorClass;
		Ar << ActorData.ActorName;
		Ar << ActorData.ActorTransform;
		Ar << ActorData.ActorData;
		return Ar;
	}
};
Method 0
USTRUCT()
struct FSaveGameData
{
	GENERATED_USTRUCT_BODY()

	FName GameID;
	FDateTime Timestamp;
	TArray<FActorSaveData> SavedActors;

	friend FArchive& operator<<(FArchive& Ar, FSaveGameData& GameData)
	{
		Ar << GameData.GameID;
		Ar << GameData.Timestamp;
		Ar << GameData.SavedActors;
		return Ar;
	}
};
*/
//Method 1
//USTRUCT()
//struct FSaveGameActorData {
//	TSubclassOf<AEmployee> EmployeeClass;
//	FString EmployeeName;
//	//FArchive& operator <<(FArchive& Ar, FSaveGameActorData& Struct)
//	//{
//	//	Ar << Struct.EmployeeClass;
//	//	Ar << Struct.EmployeeName;
//	//	return Ar;
//	//}
//};



UCLASS()
class PROJECTIDLE_API UGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UGameSave();
	UGameManager* GM;

	UPROPERTY(EditAnywhere) FVector Saved_PlayerLocation;
	UPROPERTY(EditAnywhere) int Saved_Money;
	UPROPERTY(EditAnywhere) TArray<class AItem*> InventoryList;
	UPROPERTY(EditAnywhere) TArray<class AWorkstation*> WorkstationList;
//	UPROPERTY(EditAnywhere) TArray<struct FSaveMesh> WorkstationMeshList;
	//UPROPERTY(EditAnywhere) TArray<class FSaveMesh*> WorkstationMesh;

public:
	// void SaveEmployeeRecords(FArchive Ar); Method 1
	void ClearLists();
};
