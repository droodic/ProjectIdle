// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtistDepartment.h"
#include "ProjectIdle/GameManager.h"

AArtistDepartment::AArtistDepartment() {
	DepartmentCapacity = 3;
}

void AArtistDepartment::BeginPlay() {
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	DepRole = ERole::Artist;
	GM->ArtistDepartment = this;
	GM->DepartmentList.Add(this);
}

