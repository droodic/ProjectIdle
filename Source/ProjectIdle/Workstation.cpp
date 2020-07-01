// Fill out your copyright notice in the Description page of Project Settings.


#include "Workstation.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/GameHUD.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/Department.h"
#include "Employees/Artist.h"
#include "Employees/Programmer.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
//#include "ProjectIdle/Shop/Item.h"
#include "ProjectIdle/Shop/ItemButton.h"
#include "ProjectIdle/Widgets/WorkstationUpgradeWidget.h"
#include "ProjectIdle/Widgets/WorkstationCompileWidget.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Workstation.h"

// Sets default values
AWorkstation::AWorkstation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeskMesh"));
	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComputerMesh"));
	ChairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChairMesh"));
	ChairMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyboardMesh"));
	RootComponent = DeskMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	CollisionBox->AttachTo(RootComponent);
	CollisionBox->SetBoxExtent(FVector(350, 350, 350));

	StationRole = ERole::Programmer;//Default to stop crashing

	ComputerMesh->SetupAttachment(RootComponent);
	ChairMesh->SetupAttachment(RootComponent);
	KeyboardMesh->SetupAttachment(RootComponent);

	CompileProgressBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorkloadProgressBar")); //Maybe make Employee BP to set this up, because if later Employee classes emerge if we
	CompileProgressBar->AttachTo(RootComponent);
	CompileProgressBar->SetVisibility(false);
	CompileProgressBar->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AWorkstation::BeginPlay()
{
	Super::BeginPlay();
	//IsObjectDisable = DisableObject;
	EnableStation(IsEnabled);
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->WorkStation = this;
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

	Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CompileProgressBar != nullptr) {
		auto WorkloadWidget = CompileProgressBar->GetUserWidgetObject();
		auto WidgetInstance = Cast<UWorkstationCompileWidget>(WorkloadWidget);
		WidgetInstance->WorkstationRef = this;
		CompileProgressBar->SetVisibility(false);
	}

	/*if (DefaultMonitor != nullptr && DefaultKeyboard != nullptr && DefaultDesk != nullptr && DefaultChair != nullptr)
	{
		CurrentMonitor = DefaultMonitor.GetDefaultObject();
		CurrentKeyboard = DefaultKeyboard.GetDefaultObject();
		CurrentDesk = DefaultDesk.GetDefaultObject();
		CurrentChair = DefaultChair.GetDefaultObject();
	}*/
	//DoCompile();//test
}

// Called every frame
void AWorkstation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DisableStation(DisableObject);

	//Same as employee workload diminish, move to event/timer delegate function later
	if (IsCompiling && IsEnabled) {
		if (CompileProgressBar != nullptr) {
			CompileProgressBar->SetWorldRotation(Camera->GetCameraRotation());
			CompileProgressBar->AddLocalRotation(FRotator(0, 180, 0));
		}
		if (CurrentCompileLoad > 0) {
			CurrentCompileLoad -= (DeltaTime * (5.f + CompileModifier));
			if (CurrentCompileLoad <= 0) {
				CompileProgressBar->SetVisibility(false);
				IsCompiling = false;
			}
		}
	}
}

void AWorkstation::UpdateWorkstationPosition(AEmployee* EmployeeRef)
{
	if (!HasEmployee && this->FloorLevel != -1) {
		if (this->FloorLevel == EmployeeRef->FloorLevel)
		{
			EmployeeRef->WorkstationRef = this;
			EmployeeRef->HasWorkStation = true;
			EmployeeRef->StartPosition = StationLocation;
			HasEmployee = true;
		}
	}
}

void AWorkstation::EnableStation(bool Enable)
{
	if (!Enable)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		//this->SetActorTickEnabled(true);
		IsEnabled = false;
	}
	else
	{
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		//this->SetActorTickEnabled(false);
		IsEnabled = true;
	}
}

void AWorkstation::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (!GM->IsWidgetInDisplay)
	{
		if (!UpgradeWidget->IsInViewport() && InRange)
		{
			GM-> IsWidgetInDisplay = true;
			GM->CurrentWidgetInDisplay = UpgradeWidget;

			UpgradeWidget->AddToViewport();

			if (UpgradeWidget->InventoryWrapBox->GetChildrenCount() >= 1)
			{
				UpgradeWidget->InventoryWrapBox->ClearChildren();
			}
		}
	}
	else if (GM->IsWidgetInDisplay && InRange)
	{
		GM->IsWidgetInDisplay = false;
		if (GM->CurrentWidgetInDisplay)
		{
			GM->CurrentWidgetInDisplay->RemoveFromViewport();
		}

		if (!UpgradeWidget->IsInViewport() && InRange)
		{
			GM->IsWidgetInDisplay = true;
			GM->CurrentWidgetInDisplay = Cast<UUserWidget>(UpgradeWidget);

			UpgradeWidget->AddToViewport();

			if (UpgradeWidget->InventoryWrapBox->GetChildrenCount() >= 1)
			{
				UpgradeWidget->InventoryWrapBox->ClearChildren();
			}
		}

	}
}

void AWorkstation::UpgradeMesh(AItem* Item)
{
	switch (Item->ItemSubCategory)
	{
	case ESubCategory::Monitor:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item ID: " + FString::FromInt(Item->ItemID) + " Name: " + Item->ItemName + " Item sub: Monitor");
		break;
	case ESubCategory::Keyboard:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item ID: " + FString::FromInt(Item->ItemID) + " Name: " + Item->ItemName + " Item sub: Keyboard");
		break;
	case ESubCategory::Desk:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item ID: " + FString::FromInt(Item->ItemID) + " Name: " + Item->ItemName + " Item sub: Desk");
		break;
	case ESubCategory::Chair:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Item ID: " + FString::FromInt(Item->ItemID) + " Name: " + Item->ItemName + " Item sub: Chair");
		break;
	}

	/*AItem* CurrentItem = Item;
	for (auto item : GM->OfficeDepartment->GameItemList)
	{
		switch (Item->ItemSubCategory)
		{
		case ESubCategory::Monitor:
			if (ComputerMeshID == item.GetDefaultObject()->ItemID)
			{
				CurrentItem = item.GetDefaultObject();
			}
			break;
		case ESubCategory::Keyboard:
			if (KeyboardMeshID == item.GetDefaultObject()->ItemID)
			{
				CurrentItem = item.GetDefaultObject();
			}
			break;
		case ESubCategory::Desk:
			if (DeskMeshID == item.GetDefaultObject()->ItemID)
			{
				CurrentItem = item.GetDefaultObject();
			}
			break;
		case ESubCategory::Chair:
			if (ChairMeshID == item.GetDefaultObject()->ItemID)
			{
				CurrentItem = item.GetDefaultObject();
			}
			break;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Item ID: " + FString::FromInt(CurrentItem->ItemID) + " Name: " + CurrentItem->ItemName);

	if (GM->InventoryList.Contains(CurrentItem))
	{
		auto itemCount = GM->InventoryList.FindRef(CurrentItem);
		itemCount++;
		GM->InventoryList.Add(CurrentItem, itemCount);
	}
	else
	{
		GM->InventoryList.Add(CurrentItem, 1);
	}*/

	for (auto item : GM->OfficeDepartment->GameItemList)
	{
		switch (Item->ItemSubCategory)
		{
		case ESubCategory::Monitor:
			if (ComputerMeshID == item.GetDefaultObject()->ItemID)
			{
				if (GM->InventoryList.Contains(item.GetDefaultObject()))
				{
					auto itemCount = GM->InventoryList.FindRef(item.GetDefaultObject());
					itemCount++;
					GM->InventoryList.Add(item.GetDefaultObject(), itemCount);
				}
				else
				{
					GM->InventoryList.Add(item.GetDefaultObject(), 1);
				}
			}
			break;
		case ESubCategory::Keyboard:
			if (KeyboardMeshID == item.GetDefaultObject()->ItemID)
			{
				if (GM->InventoryList.Contains(item.GetDefaultObject()))
				{
					auto itemCount = GM->InventoryList.FindRef(item.GetDefaultObject());
					itemCount++;
					GM->InventoryList.Add(item.GetDefaultObject(), itemCount);
				}
				else
				{
					GM->InventoryList.Add(item.GetDefaultObject(), 1);
				}
			}
			break;
		case ESubCategory::Desk:
			if (DeskMeshID == item.GetDefaultObject()->ItemID)
			{
				if (GM->InventoryList.Contains(item.GetDefaultObject()))
				{
					auto itemCount = GM->InventoryList.FindRef(item.GetDefaultObject());
					itemCount++;
					GM->InventoryList.Add(item.GetDefaultObject(), itemCount);
				}
				else
				{
					GM->InventoryList.Add(item.GetDefaultObject(), 1);
				}
			}
			break;
		case ESubCategory::Chair:
			if (ChairMeshID == item.GetDefaultObject()->ItemID)
			{
				if (GM->InventoryList.Contains(item.GetDefaultObject()))
				{
					auto itemCount = GM->InventoryList.FindRef(item.GetDefaultObject());
					itemCount++;
					GM->InventoryList.Add(item.GetDefaultObject(), itemCount);
				}
				else
				{
					GM->InventoryList.Add(item.GetDefaultObject(), 1);
				}
			}
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Item ID: " + FString::FromInt(item.GetDefaultObject()->ItemID) + " Name: " + item.GetDefaultObject()->ItemName);
	}

	



	auto itemCount = GM->InventoryList.FindRef(Item);
	itemCount--;

	GM->InventoryList.Emplace(Item, itemCount);

	if (GM->InventoryList.FindRef(Item) == 0)
	{
		GM->InventoryList.Remove(Item);
	}


	if (Item->ItemSubCategory == ESubCategory::Monitor)
	{
		ComputerMesh->SetStaticMesh(Item->ItemMesh->GetStaticMesh());
		UpgradeWidget->MonitorImage->SetBrushFromTexture(Item->ItemImage);
		CompileModifier = Item->ItemCompileRate;
		ComputerMeshID = Item->ItemID;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "Current Monitor ID: " + FString::FromInt(ComputerMeshID));
	}
	else if (Item->ItemSubCategory == ESubCategory::Keyboard)
	{
		KeyboardMesh->SetStaticMesh(Item->ItemMesh->GetStaticMesh());
		UpgradeWidget->Keyboard_Img->SetBrushFromTexture(Item->ItemImage);
		KeyboardMeshID = Item->ItemID;
	}
	else if (Item->ItemSubCategory == ESubCategory::Desk)
	{
		DeskMesh->SetStaticMesh(Item->ItemMesh->GetStaticMesh());
		UpgradeWidget->Desk_Img->SetBrushFromTexture(Item->ItemImage);
		DeskMeshID = Item->ItemID;
	}
	else if (Item->ItemSubCategory == ESubCategory::Chair)
	{
		ChairMesh->SetStaticMesh(Item->ItemMesh->GetStaticMesh());
		UpgradeWidget->Chair_Img->SetBrushFromTexture(Item->ItemImage);
		ChairMeshID = Item->ItemID;
	}

	UpgradeWidget->ShowInventory(Item->ItemSubCategory);
}

void AWorkstation::UpgradeMeshFromSave() {

	for (auto Item : GM->OfficeDepartment->GameItemList) {
		if (Item.GetDefaultObject()->ItemID == ComputerMeshID) {
			ComputerMesh->SetStaticMesh(Item.GetDefaultObject()->ItemMesh->GetStaticMesh());
		}
		else if (Item.GetDefaultObject()->ItemID == DeskMeshID) {
			DeskMesh->SetStaticMesh(Item.GetDefaultObject()->ItemMesh->GetStaticMesh());
		}
		else if (Item.GetDefaultObject()->ItemID == KeyboardMeshID) {
			KeyboardMesh->SetStaticMesh(Item.GetDefaultObject()->ItemMesh->GetStaticMesh());
		}
		else if (Item.GetDefaultObject()->ItemID == ChairMeshID) {
			ChairMesh->SetStaticMesh(Item.GetDefaultObject()->ItemMesh->GetStaticMesh());
		}
	}
}

void AWorkstation::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr) {
		InRange = true;
	}
}

void AWorkstation::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr) {
		InRange = false;
		if (UpgradeWidget->IsInViewport()) {
			UpgradeWidget->RemoveFromViewport();
		}
	}
}

void AWorkstation::DoCompile() {
	IsCompiling = true;
	CompileProgressBar->SetVisibility(true);

	//Make function for generation of compile loads scaling with player progress, etc
	AssignedCompileLoad = UKismetMathLibrary::RandomFloatInRange(50, 100);
	CurrentCompileLoad = AssignedCompileLoad;
}

void AWorkstation::UpdateSupervisorWorkstationPosition()
{
	if (!HasEmployee) {
		int32 employeeSize = GM->EmployeeList.Num();
		int32 workstationSize = GM->WorkstationList.Num();
		FVector AStationLocation = this->GetActorLocation();

		for (auto Department : GM->DepartmentList)
		{
			//Department->SupervisorRef->WorkstationRef = this;
			//Department->SupervisorRef->HasWorkStation = true;
			Department->SupervisorRef->StartPosition = StationLocation;
			//HasEmployee = true;
		}
	}
}

void AWorkstation::WorkstationInit(ERole Station)
{
	StationRole = Station;
}