// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"

ASupervisor::ASupervisor() {
	Salary = 100.f;
	Roles = ERole::Programmer;
	Position = EPosition::Supervisor;
	EmployeeRole = "Supervisor"; //temp
}

// Sets default values
ASupervisor::ASupervisor(ERole Department)
{
	Salary = 100.f;
	Roles = Department;
	Position = EPosition::Supervisor;
	EmployeeRole = "Supervisor"; //temp

}
