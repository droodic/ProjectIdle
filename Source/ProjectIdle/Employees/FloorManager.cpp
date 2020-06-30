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
	//AutomateTasks();
	StartPosition = GM->OfficeDepartment->ChairMesh->GetComponentLocation();
	MoveEmployee(StartPosition);
	//MoveEmployee(StartPosition);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "...");

}

//STATE Machine ?
void AFloorManager::Tick(float DeltaTime) {
	if (AutoManaging) {
		//Start idea gen state
		if (IdeaGenerationState && !AI->IsMoving && !GM->OfficeDepartment->IsGenerating) {
			GM->OfficeDepartment->GenerateIdea();
			GeneratingIdea = true;
			IdeaGenerationState = false;
		}

		//Start meeting state
		if (MeetingState && !AI->IsMoving) {
			//call meeting handled by ideabacklog widget function after, migrate somehow here? 
			//MAKE THIS TIMER, CALLED VERY OFTEN, or find better way
			GM->MeetingDepartment->BackFromMeeting();
			if (GM->MeetingDepartment->CanReturn) {
				MeetingState = false;
				IdeaInProductionState = true;
			}
		}
		//Restart loop when idea finished
		if (IdeaInProductionState) {
			if (!GM->IdeaInProduction) {
				AutomateTasks();
				IdeaInProductionState = false;
			}
		}
	}

}

void AFloorManager::AutomateTasks(bool PlayerInput) {

	if (AutoManaging && PlayerInput) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Turning off Manager");
		AutoManaging = false;
		MoveEmployee(StartPosition, 25.f);
		return;
	}
	else {
		AutoManaging = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Starting loop");
		if (!IdeaGenerationState) {
			if (FVector::Dist(GetActorLocation(), GM->OfficeDepartment->ChairMesh->GetComponentLocation()) <= 115.0f) {
				AI->IsMoving = false;
				IdeaGenerationState = true;
			}
			else {
				MoveEmployee(StartPosition, 25.f);
				IdeaGenerationState = true;
			}

		}
		return;
	}




}