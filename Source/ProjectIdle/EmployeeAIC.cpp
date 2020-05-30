// Fill out your copyright notice in the Description page of Project Settings.


#include "DetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "EmployeeAIC.h"


AEmployeeAIC::AEmployeeAIC(const FObjectInitializer& ObjectInitializer) 

	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))){

}

void AEmployeeAIC::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

}
