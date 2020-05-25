// Fill out your copyright notice in the Description page of Project Settings.


#include "Workstation.h"
#include "ProjectIdle/GameManager.h"
#include "Engine.h"

// Sets default values
AWorkstation::AWorkstation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeskMesh"));
	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComputerMesh"));
	RootComponent = DeskMesh;

	ComputerMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorkstation::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->WorkstationList.Add(this);
	StationLocation = this->GetActorLocation();
}

// Called every frame
void AWorkstation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorkstation::UpdateWorkstationPosition()
{
	int32 employeeSize = GM->EmployeeList.Num();
	int32 workstationSize = GM->WorkstationList.Num();
	FVector testing = FVector(0, 0, 0);

	if (employeeSize > 0 && workstationSize > 0)
	{
		for (int i = 0; i < employeeSize; i++)
		{
			GM->EmployeeList[i]->StartPosition = testing;
		}
	}

}
