// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"
#include "ProjectIdle/GameManager.h"

ASupervisor::ASupervisor() {
	Salary = 100.f;
	EmployeeRole = ERole::Programmer;
	Position = EPosition::Supervisor;
}

// Sets default values
ASupervisor::ASupervisor(ERole Department)
{
	Salary = 100.f;
	EmployeeRole = Department;
	Position = EPosition::Supervisor;

}


void ASupervisor::BeginPlay()
{
	Super::BeginPlay();

	if (EmployeeRole == ERole::Programmer) {
		GM->ProgrammingDepartment->HasSupervisor = true;
		GM->ProgrammingDepartment->SupervisorRef = this;
	}
	else if (EmployeeRole == ERole::Artist) {
		GM->ArtistDepartment->HasSupervisor = true;
		GM->ArtistDepartment->SupervisorRef = this;
	}
}

