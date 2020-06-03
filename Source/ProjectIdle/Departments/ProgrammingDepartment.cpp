// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectIdle\GameManager.h"
#include "ProgrammingDepartment.h"

AProgrammingDepartment::AProgrammingDepartment() {
	DepartmentCapacity = 3;
}

void AProgrammingDepartment::BeginPlay() {
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->ProgrammingDepartment = this;
}