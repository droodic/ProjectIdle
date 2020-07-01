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
	void AutomateTasks(bool PlayerInput = false);

	//quick test iteration, State machine later?
	UPROPERTY(SaveGame) bool AutoManaging;
	UPROPERTY(SaveGame, BlueprintReadWrite) bool IdeaInProductionState;
	UPROPERTY(SaveGame, BlueprintReadWrite) bool IdeaGenerationState;
	UPROPERTY(SaveGame, BlueprintReadWrite) bool MeetingState;
	UPROPERTY(SaveGame, BlueprintReadWrite) bool AllAtMeeting;
	UPROPERTY(SaveGame, BlueprintReadWrite) bool GeneratingIdea;
	int IdeaIndex = 0;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
