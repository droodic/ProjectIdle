// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorManager.h"
//#include "ProjectIdle/GameManager.h"
//#include "ProjectIdle/OfficeDepartment.h"

AFloorManager::AFloorManager() {
	EmployeeRole = ERole::Programmer; //?
	Position = EPosition::FloorManager;
}

void AFloorManager::BeginPlay() {
	Super::BeginPlay();
	//dont call super, check if need regular Employee Position check then
	GM->OfficeDepartment->ManagerRef = this;
	AutomateTasks();
	//MoveEmployee(StartPosition);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "...");

}

void AFloorManager::Tick(float DeltaTime) {
	//Start idea gen state
	if (IdeaGenerationState && !AI->IsMoving && !GM->OfficeDepartment->IsGenerating) {
		GM->OfficeDepartment->GenerateIdea();
		GeneratingIdea = true;
		IdeaGenerationState = false;
	}
	//Start meeting state
	if (MeetingState && !AI->IsMoving) {
		//call meeting handled by ideabacklog widget function after, migrate somehow here? 
		//MAKE THIS TIMER, CALLED VERY OFTEN
		GM->MeetingDepartment->BackFromMeeting();

		if (GM->MeetingDepartment->CanReturn) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Backfrommeetingcall");
			MeetingState = false;
			IdeaInProductionState = true;
		}

		//also problem with assigning workload, floormanager given workload?
		//MeetingState = false;
	}
	if (IdeaInProductionState) {
		if (!GM->IdeaInProduction) {
			AutomateTasks();
			IdeaInProductionState = false;
		}
	}
}

void AFloorManager::AutomateTasks() {
	if (!IdeaGenerationState) {
		MoveEmployee(GM->OfficeDepartment->GetActorLocation());
		IdeaGenerationState = true;
	}
}