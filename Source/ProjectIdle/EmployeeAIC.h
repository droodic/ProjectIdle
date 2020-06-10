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
	AEmployeeAIC(const FObjectInitializer& ObjectInitializer);
	class AEmployee* EmployeeRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsMoving = false;
protected:
	//	AEmployeeAIC(const FObjectInitializer& ObjectInitializer);
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	//virtual void OnPossess(APawn* InPawn);
};
