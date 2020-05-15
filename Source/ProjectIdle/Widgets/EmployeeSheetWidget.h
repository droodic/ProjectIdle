// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "ProjectIdle/Employees/Employee.h"
#include "EmployeeSheetWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UEmployeeSheetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Morale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Performance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Salary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString EmployeeRole;
	
};
