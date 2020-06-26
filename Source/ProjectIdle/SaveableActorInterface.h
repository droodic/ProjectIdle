// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
//#include "Inventory/MasteringInventory.h"
#include "SaveableActorInterface.generated.h"

/**
 *
 */
USTRUCT()
struct FWorkstationSavedData
{
	GENERATED_USTRUCT_BODY()
		TArray<uint8> WorkstationMesh;
		//UStaticMeshComponent ComputerMesh;
		//UStaticMeshComponent ChairMesh;
		//UStaticMeshComponent KeyboardMesh;

		friend FArchive& operator<<(FArchive& Ar, FWorkstationSavedData& WorkstationData)
		{
			Ar << WorkstationData.WorkstationMesh;

			return Ar;
		}
};

USTRUCT()
struct FActorSavedData
{
	GENERATED_USTRUCT_BODY()

	FString MyClass;
	FTransform MyTransform;
	// FVector MyVelocity;
	FName MyName;
	TArray<uint8> MyData;

	friend FArchive& operator<<(FArchive& Ar, FActorSavedData& SavedData)
	{
		Ar << SavedData.MyClass;
		Ar << SavedData.MyTransform;
		Ar << SavedData.MyName;
		Ar << SavedData.MyData;
		return Ar;
	}
};

USTRUCT()
struct FGameSavedData
{
	GENERATED_USTRUCT_BODY()

	FDateTime Timestamp;
	FName MapName;
	//FInventorySaveData InventoryData;
	//TArray<FWorkstationSavedData> SavedWorkstations;
	TArray<FActorSavedData> SavedActors;

	friend FArchive& operator<<(FArchive& Ar, FGameSavedData& GameData)
	{
		//Ar << GameData.MapName;
		Ar << GameData.Timestamp;
		Ar << GameData.SavedActors;
		return Ar;
	}
};

struct FSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FSaveGameArchive(FArchive& InInnerArchive)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, true)
	{
		ArIsSaveGame = true;
	}
};

UINTERFACE(BlueprintType)
class USaveableActorInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISaveableActorInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Load-Save")
		void ActorSaved();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Load-Save")
		void ActorLoaded();
};