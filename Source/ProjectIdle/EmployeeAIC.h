// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EmployeeAIC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AEmployeeAIC : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GoMeeting();
};
