// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"
#include "ProjectIdle/GameManager.h"

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


void ASupervisor::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = FVector(0, 0, 0);

}

void ASupervisor::InitSupervisor(ERole Department) {
	if (Department == ERole::Programmer) {
		GM->ProgrammingDepartment->HasSupervisor = true;
		GM->ProgrammingDepartment->SupervisorRef = this;
	}
	else if (Department == ERole::Artist) {
		GM->ArtistDepartment->HasSupervisor = true;
		GM->ArtistDepartment->SupervisorRef = this;
	}
}

