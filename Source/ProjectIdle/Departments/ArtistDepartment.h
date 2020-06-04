// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectIdle/Department.h"
#include "ArtistDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AArtistDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	AArtistDepartment();
	class UGameManager* GM;

protected:
	virtual void BeginPlay() override;
};
