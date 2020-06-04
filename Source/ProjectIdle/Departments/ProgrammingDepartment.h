// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectIdle/Department.h"
#include "ProgrammingDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AProgrammingDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	AProgrammingDepartment();
	class UGameManager* GM;

protected:
	virtual void BeginPlay() override;
};
