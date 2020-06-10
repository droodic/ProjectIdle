// Fill out your copyright notice in the Description page of Project Settings.


#include "Workstation.h"
#include "ProjectIdle/GameManager.h"
#include "Employees/Artist.h"
#include "ProjectIdle/GameHUD.h"
#include "Employees/Programmer.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
#include "ProjectIdle/Widgets/WorkstationUpgradeWidget.h"
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

	UpgradeMonitor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpgradeMonitor"));
	UpgradeKeyboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpgradeKeyBoard"));
	//UpgradeChair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UpgradeChair"));

	UpgradeMonitor->SetupAttachment(RootComponent);
	UpgradeKeyboard->SetupAttachment(RootComponent);
	ComputerMesh->SetupAttachment(RootComponent);
	ChairMesh->SetupAttachment(RootComponent);
	KeyboardMesh->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AWorkstation::BeginPlay()
{
	Super::BeginPlay();
	IsObjectDisable = DisableObject;
	DisableStation(DisableObject);
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->WorkstationList.Add(this);
	GM->WorkStation = this;
	HasEmployee = false;
	StationLocation = ChairMesh->GetComponentLocation();
	
	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0));




	if (UserWidget != nullptr)
	{
		UpgradeWidget = CreateWidget<UWorkstationUpgradeWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidget);
	}
	if (UpgradeWidget)
	{
		UpgradeWidget->Station = this;
	}



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
	
	//int32 workstationSize = WorkstationActiveLenght();
	//FString mouseY = FString::FromInt(workstationSize);
	//UE_LOG(LogActor, Warning, TEXT("%s"), *mouseY)
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
	int32 activeWorkstation = WorkstationActiveLenght();
	int32 workstationSize = GM->WorkstationList.Num();
	FVector AStationLocation = this->GetActorLocation();

		for (int i = 0; i < workstationSize; i++)
		{
			if (!GM->WorkstationList[i]->DisableObject)
			{
				if (GM->WorkstationList[i]->IsA(AProgrammerStation::StaticClass()))
				{
					if (GM->WorkstationList[i]->HasEmployee == false)
					{
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

				else if (GM->WorkstationList[i]->IsA(AArtistStation::StaticClass()))
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
}



void AWorkstation::DisableStation(bool Disable)
{
	if (Disable)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
	    this->SetActorTickEnabled(true);
	}
	else
	{
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		////Turn off if active
		this->SetActorTickEnabled(false);
	}
}

int AWorkstation::WorkstationActiveLenght()
{
	int count = 0;
	int length = GM->WorkstationList.Num();

	for (int i = 0; i < length; i++)
	{
		if (!GM->WorkstationList[i]->IsObjectDisable)
		{
			count++;
		}
	}
	return count;
}

void AWorkstation::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (!UpgradeWidget->IsInViewport())
	{
		UpgradeWidget->AddToViewport();
		//UpgradeMesh(0);
		//UpgradeMesh(1);
	}
	else
	{
		UpgradeWidget->RemoveFromViewport();
	}

	//UI->ShowStationUpgrade(this);
}

void AWorkstation::UpgradeMesh(int Index)
{
	if (Index == 0)
	{
		ComputerMesh->SetVisibility(false);
		UpgradeMonitor->SetVisibility(true);
	}
	if (Index == 1)
	{
		KeyboardMesh->SetVisibility(false);
		UpgradeKeyboard->SetVisibility(true);
	}
}