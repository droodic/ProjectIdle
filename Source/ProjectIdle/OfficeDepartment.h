// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Department.h"
#include "OfficeDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AOfficeDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void CallMeeting();


	//public?
	UPROPERTY(EditAnywhere) int ideasGenerated;
	UPROPERTY(BlueprintReadWrite) float ideaProgress;

};
