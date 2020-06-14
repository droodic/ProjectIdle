// Fill out your copyright notice in the Description page of Project Settings.


#include "Workstation.h"
#include "ProjectIdle/GameManager.h"
#include "Employees/Artist.h"
#include "Employees/Programmer.h"
#include "ProjectIdle/GameHUD.h"
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

	StationRole = ERole::Programmer;//Default to stop crashing
}

// Called when the game starts or when spawned
void AWorkstation::BeginPlay()
{
	Super::BeginPlay();
	//IsObjectDisable = DisableObject;
	EnableStation(IsEnabled);
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->WorkstationList.Add(this);
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
}

// Called every frame
void AWorkstation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DisableStation(DisableObject);
}

void AWorkstation::UpdateWorkstationPosition()
{
	if (!HasEmployee) {
		int32 employeeSize = GM->EmployeeList.Num();
		int32 workstationSize = GM->WorkstationList.Num();
		FVector AStationLocation = this->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(12312542, 5, FColor::Green, "Update Station");


		for (auto Employee : GM->EmployeeList) {
			if (!Employee->HasWorkStation && Employee->EmployeeRole == StationRole && IsEnabled) {
				Employee->WorkstationRef = this;
				Employee->HasWorkStation = true;
				Employee->StartPosition = StationLocation;
				HasEmployee = true;
			}
		}
	}
}

void AWorkstation::EnableStation(bool Enable)
{
	if (!Enable)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		this->SetActorTickEnabled(true);
		IsEnabled = false;
	}
	else
	{
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		this->SetActorTickEnabled(false);
		IsEnabled = true;
	}
}


void AWorkstation::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (!UpgradeWidget->IsInViewport())
	{
		UpgradeWidget->AddToViewport();
	}
	else
	{
		UpgradeWidget->RemoveFromViewport();
	}
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
	UpgradeWidget->RemoveFromViewport();
}

//void AWorkStation::DoCompile() {
//
//}