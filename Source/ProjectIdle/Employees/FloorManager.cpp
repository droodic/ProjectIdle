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
				GEngine->AddOnScreenDebugMessage(120941, 5.f, FColor::Green, "BackfromMeetingcall");
				MeetingState = false;
				IdeaInProductionState = true;
			}
		}
		if (IdeaInProductionState) {
			if (!GM->IdeaInProduction) {
				AutomateTasks();
				IdeaInProductionState = false;
			}
		}
	}

}

void AFloorManager::AutomateTasks() {
	if (!AutoManaging) {
		AutoManaging = true;
		if (!IdeaGenerationState) {
			if (FVector::Dist(GetActorLocation(), GM->OfficeDepartment->ChairMesh->GetComponentLocation()) <= 100.0f) {
				AI->IsMoving = false;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "at desk");
				IdeaGenerationState = true;
			}
			else {
				MoveEmployee(StartPosition);
				IdeaGenerationState = true;
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "automate");

		}
	}
	else if (AutoManaging) {
		AutoManaging = false;
		MoveEmployee(StartPosition);
	}

}