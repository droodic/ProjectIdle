// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employee.h"
#include "FloorManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AFloorManager : public AEmployee
{
	GENERATED_BODY()
public:
	AFloorManager();
	void AutomateTasks();

	//quick test iteration, State machine later?
	bool IdeaInProductionState;
	bool IdeaGenerationState;
	bool MeetingState;
	bool GeneratingIdea;
	int IdeaIndex = 0;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
