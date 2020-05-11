// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Idea.h"
#include "Department.h"
#include "GameManager.h"
#include "Employees\Employee.h"
#include "EmployeeAIC.h"
#include "OfficeDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AOfficeDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	UGameManager* GM;
	
	
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void CallMeeting();

	TArray<class Idea*> IdeaList;
	bool IsGenerating;
	virtual void Tick(float DeltaTime) override;
	
	//public?
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;
	UPROPERTY(BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(BlueprintReadWrite) float MaxIdeaProgress = 100;

};
