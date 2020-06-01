// Fill out your copyright notice in the Description page of Project Settings.


#include "Workstation.h"
#include "ProjectIdle/GameManager.h"
#include "Employees/Artist.h"
#include "Employees/Programmer.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
#include "Engine.h"

// Sets default values
AWorkstation::AWorkstation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeskMesh"));
	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComputerMesh"));
	ChairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChairMesh"));
	KeyboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyboardMesh"));
	RootComponent = DeskMesh;

	ComputerMesh->SetupAttachment(RootComponent);
	ChairMesh->SetupAttachment(RootComponent);
	KeyboardMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWorkstation::BeginPlay()
{
	Super::BeginPlay();

	GM = GetWorld()->GetGameInstance<UGameManager>();
	DisableStation(DisableObject);
	GM->WorkstationList.Add(this);
	GM->WorkStation = this;
	
	StationLocation = ChairMesh->GetComponentLocation();
	
	//FVector zero = FVector(200, 0, 0);
	//StationVector = this->GetActorLocation();
	//FRotator rotation = this->GetActorRotation();

	//StationLocation = DeskMesh->GetSocketLocation("TransformSocket");
	//ChairMesh->Getforw
	/*if (rotation.Yaw == 0 || rotation.Yaw == 360)
	{
		StationLocation = this->StationLocation = DeskMesh->GetSocketLocation("TransformSocket").operator+(zero);
		
	}
	else
	{
		StationLocation = StationLocation = DeskMesh->GetSocketLocation("TransformSocket").operator-(zero);
	}*/
	
	HasEmployee = false;

	//int32 workstationSize = GM->WorkstationList.Num();
	//FString mouseY = FString::FromInt(workstationSize);
	//UE_LOG(LogActor, Warning, TEXT("%s"), *mouseY)
	//UE_LOG(LogActor, Warning, TEXT("%s"), *StationLocation.ToString())
}

// Called every frame
void AWorkstation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DisableStation(DisableObject);
}

void AWorkstation::UpdateWorkstationPosition()
{
	int32 employeeSize = GM->EmployeeList.Num();
	int32 workstationSize = WorkstationActiveLenght();
	FVector AStationLocation = this->GetActorLocation();
	FVector testing = FVector(0, 0, 0);

	for (int i = 0; i < workstationSize; i++)
	{
		if (GM->WorkstationList[i]->IsA(AProgrammerStation::StaticClass()))
		{
			if (GM->WorkstationList[i]->HasEmployee == false)
			{
				FVector current = GM->WorkstationList[i]->StationLocation;
				for (int j = 0; j < employeeSize; j++)
				{
					if (GM->EmployeeList[j]->IsA(AProgrammer::StaticClass()) && GM->EmployeeList[j]->HasWorkStation == false)
					{
						GM->WorkstationList[i]->HasEmployee = true;
						GM->EmployeeList[j]->HasWorkStation = true;
						GM->EmployeeList[j]->StartPosition = GM->WorkstationList[i]->StationLocation;
						GM->EmployeeList[j]->WorkstationPositionRef = i;
						break;
					}
				}
			}
		}

		if (GM->WorkstationList[i]->IsA(AArtistStation::StaticClass()))
		{
			if (GM->WorkstationList[i]->HasEmployee == false)
			{
				for (int j = 0; j < employeeSize; j++)
				{
					if (GM->EmployeeList[j]->IsA(AArtist::StaticClass()) && GM->EmployeeList[j]->HasWorkStation == false)
					{
						GM->WorkstationList[i]->HasEmployee = true;
						GM->EmployeeList[j]->HasWorkStation = true;
						GM->EmployeeList[j]->StartPosition = GM->WorkstationList[i]->StationLocation;
						GM->EmployeeList[j]->WorkstationPositionRef = i;
						break;
					}
				}
			}
		}
	}
}

void AWorkstation::DisableStation(bool Disable)
{
	if (Disable)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		//Turn off if active
	    this->SetActorTickEnabled(true);
	}
	else
	{
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		this->SetActorTickEnabled(false);
	}
}

int AWorkstation::WorkstationActiveLenght()
{
	int count = 0;
	int length = GM->WorkstationList.Num();

	for (int i = 0; i < length; i++)
	{
		if (!GM->WorkstationList[i]->DisableObject)
		{
			count++;
		}
	}
	return count;
}