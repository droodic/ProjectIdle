// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employee.h"
#include "Supervisor.generated.h"

UCLASS()
class PROJECTIDLE_API ASupervisor : public AEmployee
{
	GENERATED_BODY()

public:
	//class UGameManager* GM;
	// Sets default values for this character's properties
	ASupervisor(ERole Department);
	ASupervisor();
	void InitSupervisor(ERole Department);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
