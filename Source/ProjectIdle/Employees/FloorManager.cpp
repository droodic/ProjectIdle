// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorManager.h"
//#include "ProjectIdle/GameManager.h"
//#include "ProjectIdle/OfficeDepartment.h"

AFloorManager::AFloorManager() {
	EmployeeRole = ERole::Management; //?
	Position = EPosition::FloorManager;
}

void AFloorManager::BeginPlay() {
	Super::BeginPlay();
	GM->OfficeDepartment->ManagerRef = this;
	StartPosition = GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->ChairMesh->GetComponentLocation();
	MoveEmployee(StartPosition);

}

//STATE Machine ?
void AFloorManager::Tick(float DeltaTime) {
	if (AutoManaging) {
		//Start idea gen state
		if (IdeaGenerationState && !AI->IsMoving && !GM->OfficeDepartment->IsGenerating) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Manager gen idea");

			//GM->OfficeDepartmentList[0]->GenerateIdea();
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
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Manager backfrommeeting");

				MeetingState = false;
				IdeaInProductionState = true;
			}
		}
		//Restart loop when idea finished
		if (IdeaInProductionState) {
			if (!GM->IdeaInProduction) {
				AutomateTasks();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Manager restartloop");

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
			if (FVector::Dist(GetActorLocation(), GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->ChairMesh->GetComponentLocation()) <= 115.0f) {
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