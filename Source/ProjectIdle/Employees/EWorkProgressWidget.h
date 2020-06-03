// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employee.h"
#include "Blueprint\UserWidget.h"
#include "EWorkProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UEWorkProgressWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		AEmployee* EmployeeRef;
};
