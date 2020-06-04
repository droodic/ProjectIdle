// Fill out your copyright notice in the Description page of Project Settings.


#include "EmployeeAIC.h"
#include "DetourCrowdAIController.h"
#include "Engine.h"
#include "Navigation/CrowdFollowingComponent.h"


AEmployeeAIC::AEmployeeAIC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))){


}

void AEmployeeAIC::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	GEngine->AddOnScreenDebugMessage(2215, 5, FColor::Green, TEXT("path complete?"));
	IsMoving = false;
}

