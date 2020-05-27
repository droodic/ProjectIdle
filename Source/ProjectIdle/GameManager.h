// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
	int NumOfProgrammers;
	int NumOfArtists;
	UPROPERTY(BlueprintReadWrite) TArray<class AChair*> MeetingChairList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWorkstation*> WorkstationList;

	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;
	UPROPERTY(BlueprintReadWrite) class AMeetingDepartment* MeetingDepartment;
	UPROPERTY(BlueprintReadWrite) class AWorkstation* WorkStation;
	virtual void Init();
};
