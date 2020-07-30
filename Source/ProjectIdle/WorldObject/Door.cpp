// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Employees/Employee.h"
#include "Components/MeshComponent.h"
#include "ProjectIdle/ProjectIdleCharacter.h"
#include "ProjectIdle/GameHUD.h"
#include "Engine/World.h"

// Sets default values
ADoor::ADoor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	DoorFrameMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	CollisionBox->AttachTo(DoorMesh);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Door = this;
	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (StartingDoor)
	{
		GM->DoorList.Add(this);
	}
	else
	{
		GM->UnassignedDoorList.Add(this);
	}
	//DoorLocation = this->GetActorLocation();
}

//Fire Employee
void ADoor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto Emp = Cast<AEmployee>(OtherActor);
	auto Player = Cast<AProjectIdleCharacter>(OtherActor);

	if (Emp != nullptr && Emp->IsFired)
	{
		Emp->FiredFinal();
		//UI->ShowWidget(OfficeDepMenuWidget, UserWidgets[1]); 
	}

	//if (Player != nullptr && GM->IsFloorUpgraded)
	//{
	//	if (Player->CurrentFloor == 1)
	//	{
	//	    GM->Character->PlayerControl->PlayerCameraManager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, true, true);
	//		Player->SetActorLocation(GM->DoorList[1]->SpawnPoint->GetComponentLocation());
	//		Player->CurrentFloor = 2;
	//		UI->MoneyWidget->ShowANotification("Welcome to Floor 2");
	//		return;
	//	}

	//	if (Player->CurrentFloor == 2)
	//	{
	//		GM->Character->PlayerControl->PlayerCameraManager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, true, true);
	//		Player->SetActorLocation(GM->DoorList[0]->SpawnPoint->GetComponentLocation());
	//		Player->CurrentFloor = 1;
	//		UI->MoneyWidget->ShowANotification("Welcome to Floor 1");
	//		return;
	//	}
	//}
}

