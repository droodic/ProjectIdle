// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"

ASupervisor::ASupervisor() {
	Salary = 100.f;
	Position = EPosition::Supervisor;
}

// Sets default values
ASupervisor::ASupervisor(ERole Department)
{
	Salary = 100.f;
	EmployeeRole = Department;
	Position = EPosition::Supervisor;
}

void ASupervisor::EvaluateEmployee() {
	auto Count = 0;
	for (auto Departments : GM->DepartmentList) {
		if (Departments->DepRole == EmployeeRole) {
			Count = Departments->EmpCount;
		}
	}

	for (auto DepartmentEmployee : GM->EmployeeList) {
		if (DepartmentEmployee->EmployeeRole == EmployeeRole && !DepartmentEmployee->HasBeenEvaluated && !IsEvaluating && Cast<ASupervisor>(DepartmentEmployee) == nullptr && DepartmentEmployee->IsWorking) {
			EmployeeToEval = DepartmentEmployee;
			MoveEmployee(EmployeeToEval->GetActorLocation(), 75.f);
			IsEvaluating = true;
		}
		else if (DepartmentEmployee->HasBeenEvaluated) {
			Count--;
			if (Count == 0) { //Scouting over
				MoveEmployee(StartPosition);
			}
		}
	}
}

void ASupervisor::BeginPlay()
{
	Super::BeginPlay();
	//StartPosition = FVector(0, 0, 0);


	//GM->WorkStation->UpdateWorkstationPosition();
	for (auto Workstation : GM->WorkstationList) {
		if (Workstation->IsEnabled == true && !Workstation->HasEmployee && Workstation->StationRole == EmployeeRole && Workstation->StationOwnerPosition == EPosition::Supervisor && Workstation->FloorLevel == this->FloorLevel) {
			Workstation->UpdateWorkstationPosition(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Assigning Sup Workstation");
			break;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Looping Workstation");
	}
	//IsDepartmentWorking();
	MoveEmployee(StartPosition);


}
void ASupervisor::CheckForHelp() {
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Supervisor checking for help");

	if (!IsEvaluating) {
		if (CheckingForHelp) {
			if (FVector::Dist(GetActorLocation(), TargetEmployee->GetActorLocation()) <= 250) {
				TargetEmployee->NeedAssistance = false;
				TargetEmployee->HelpWidget->SetVisibility(false);
				MoveEmployee(StartPosition);
				CheckingForHelp = false;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Supervisor helped employee, returning");

			}
		}

		if (!CheckingForHelp) {
			for (auto Employee : GM->EmployeeList) {
				if (Employee->EmployeeRole == EmployeeRole && Employee->IsWorking && Employee->CurrentWorkload > 0 && Employee->NeedAssistance) {
					MoveEmployee(Employee->GetActorLocation(), 100.f);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Moving to help employee");

					CheckingForHelp = true;
					TargetEmployee = Employee;
					//Employee->NeedAssistance = false;
					break;
				}
			}
		}
	}

	

}

void ASupervisor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	if (IsEvaluating && !AI->IsMoving) {
		if (!IsWorking) {
			WorkProgressBar->SetVisibility(true);
			AssignedWorkload = 10.f;
			CurrentWorkload = AssignedWorkload;
			IsWorking = true;
		}
		//Implement progress bar calc here
		if (WorkProgressBar != nullptr && IsWorking) {
			WorkProgressBar->SetWorldRotation(Camera->GetCameraRotation());
			WorkProgressBar->AddLocalRotation(FRotator(0, 180, 0));
			CurrentWorkload -= DeltaTime * 1.25f;
		}

		if (CurrentWorkload <= 0) {
			IsEvaluating = false;
			IsWorking = false;
			EmployeeToEval->HasBeenEvaluated = true;
			//MoveEmployee(StartPosition);
			EvaluateEmployee();
			WorkProgressBar->SetVisibility(false);
		}

	}

	//if (GM->IdeaInProduction && !CheckingForHelp) {
	//	CheckingForHelp = true;
	//	GetWorldTimerManager().SetTimer(HelpTimer, this, &ASupervisor::CheckForHelp, 2.5f, true);
	//}

}

void ASupervisor::InitSupervisor(ERole Department) {

	if (GM->Character) {
		this->FloorLevel = GM->Character->CurrentFloor;
	}

	if (Department == ERole::Programmer) {
		this->EmployeeRole = Department;
		GM->ProgrammingDepartment->HasSupervisor = true;
		GM->ProgrammingDepartment->SupervisorRef = this;
		GM->FloorList[GM->Character->CurrentFloor - 1]->ProgrammerSupOnCurrentFloor = true;
	}
	else if (Department == ERole::Artist) {
		this->EmployeeRole = Department;
		GM->ArtistDepartment->HasSupervisor = true;
		GM->ArtistDepartment->SupervisorRef = this;
		GM->FloorList[GM->Character->CurrentFloor - 1]->ArtistSupOnCurrentFloor = true;
	}
	//EvaluateEmployee();
}

void ASupervisor::FiredFinal()
{
	Super::FiredFinal();
	if (EmployeeRole == ERole::Programmer) {
		GM->ProgrammingDepartment->HasSupervisor = false;
		GM->FloorList[GM->Character->CurrentFloor - 1]->ProgrammerSupOnCurrentFloor = false;
		GM->ProgrammingDepartment->SupervisorRef = nullptr;
		GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->OfficeDepMenuWidget->Hire_ProgSup_Btn->SetIsEnabled(true);
	}
	else if (EmployeeRole == ERole::Artist) {
		GM->ArtistDepartment->HasSupervisor = false;
		GM->FloorList[GM->Character->CurrentFloor - 1]->ArtistSupOnCurrentFloor = false;
		GM->ArtistDepartment->SupervisorRef = nullptr;
		GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->OfficeDepMenuWidget->Hire_ArtistSup_Btn->SetIsEnabled(true);

	}
}

void ASupervisor::BeginSupervisorWork()
{
	//CheckingForHelp = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Supervisor beginwork for help");

	GetWorldTimerManager().SetTimer(HelpTimer, this, &ASupervisor::CheckForHelp, 2.5f, true);
}


