// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"

ASupervisor::ASupervisor() {
	Salary = 100.f;
	EmployeeRole = ERole::Programmer;
	Position = EPosition::Supervisor;
	EmployeeRole = ERole::Programmer;
}

// Sets default values
ASupervisor::ASupervisor(ERole Department)
{
	Salary = 100.f;
	EmployeeRole = Department;
	Position = EPosition::Supervisor;

}
