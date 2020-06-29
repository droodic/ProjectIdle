// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employee.h"
#include "ProjectIdle/GameManager.h"
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
	bool AutoManaging;
	UPROPERTY(BlueprintReadWrite) bool IdeaInProductionState;
	UPROPERTY(BlueprintReadWrite) bool IdeaGenerationState;
	UPROPERTY(BlueprintReadWrite) bool MeetingState;
	UPROPERTY(BlueprintReadWrite) bool AllAtMeeting;
	UPROPERTY(BlueprintReadWrite) bool GeneratingIdea;
	int IdeaIndex = 0;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
