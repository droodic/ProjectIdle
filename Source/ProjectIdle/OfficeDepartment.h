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
	void GenerateIdea();

private:
	UPROPERTY(EditAnywhere) int ideasGenerated;
	UPROPERTY(EditAnywhere) float ideaProgress;

};
