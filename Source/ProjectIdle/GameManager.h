// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WorldObject/Door.h"
#include "MeetingDepartment.h"
#include "Department.h"
#include "Departments/ProgrammingDepartment.h"
#include "Departments/ArtistDepartment.h"
#include "Widgets/WorkstationUpgradeWidget.h"
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
	UPROPERTY(BlueprintReadWrite) TArray<class ADepartment*> DepartmentList;
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
	UPROPERTY(BlueprintReadWrite) class UWorkstationUpgradeWidget* Upgrade;

	UPROPERTY(BlueprintReadWrite) int EmployeeNameIndex;

	bool IdeaInProduction = false;

	virtual void Init();
};
