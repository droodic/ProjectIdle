#include "Door.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Employees/Employee.h"
#include "Components/MeshComponent.h"
#include "ProjectIdle/ProjectIdleCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Door = this;
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

	if (Player != nullptr && GM->IsFloorUpgraded)
	{
		if (Player->CurrentFloor == 1)
		{
			Player->SetActorLocation(GM->DoorList[1]->SpawnPoint->GetComponentLocation());
			Player->CurrentFloor = 2;
			return;
		}

		if (Player->CurrentFloor == 2)
		{
			Player->SetActorLocation(GM->DoorList[0]->SpawnPoint->GetComponentLocation());
			Player->CurrentFloor = 1;
			return;
		}
	}
}

