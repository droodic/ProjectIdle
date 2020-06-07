// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WorldObject/Door.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameManager();
	UPROPERTY(BlueprintReadWrite) TArray<class AEmployee*> EmployeeList;
	UPROPERTY(BlueprintReadWrite) int NumOfProgrammers;
	UPROPERTY(BlueprintReadWrite) int NumOfArtists;
	UPROPERTY(BlueprintReadWrite) int Money;
	UPROPERTY(BlueprintReadWrite) TArray<class AChair*> MeetingChairList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWorkstation*> WorkstationList;

	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;
	UPROPERTY(BlueprintReadWrite) class AMeetingDepartment* MeetingDepartment;
	UPROPERTY(BlueprintReadWrite) class AProgrammingDepartment* ProgrammingDepartment;
	UPROPERTY(BlueprintReadWrite) class AArtistDepartment* ArtistDepartment;

	UPROPERTY(BlueprintReadWrite) class AWorkstation* WorkStation;
	UPROPERTY(BlueprintReadWrite) class ADoor* Door;

	UPROPERTY(BlueprintReadWrite) int EmployeeNameIndex;

	virtual void Init();


};
