// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "ProjectIdle/GameManager.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/Workstation.h"
#include "Door.h"


// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	Material = CreateDefaultSubobject<UMaterial>(TEXT("Material"));
	UpgradeMaterial = CreateDefaultSubobject<UMaterial>(TEXT("UpdMaterial"));
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	EnableObject(IsEnabled);
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Wall = this;
	
	if (this->Type == ObjectType::Wall)
	{
		GM->WallList.Add(this);
	}
	if (this->Type == ObjectType::Floor && StartingFloor)
	{
		GM->FloorList.Add(this);

	}
	if (this->Type == ObjectType::Floor && !StartingFloor)
	{
		GM->UnassignedFloorList.Add(this);
	}

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::UpdateWallMaterial(UMaterialInterface* NewMaterial)
{
	//Mesh->SetMaterial(0, NewMaterial);
	Mesh->SetMaterial(1, NewMaterial);
}

void AWall::UpdateWallMaterialTest()
{
	Mesh->SetMaterial(0, Material);
	Mesh->SetMaterial(1, Material);
}

void AWall::ActivateWallAndFloor()
{
	for (int i = 0; i < GM->WallList.Num(); i++)
	{
		if (!GM->WallList[i]->IsEnabled)
		{
			GM->WallList[i]->EnableObject(true);
		}
	}

	for (int i = 0; i < GM->FloorList.Num(); i++)
	{
		if (!GM->FloorList[i]->IsEnabled)
		{
			GM->FloorList[i]->EnableObject(true);
		}
	}
}

void AWall::EnableObject(bool Enable)
{
	if (!Enable)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		//IsEnabled = false;
	}
	else
	{
		this->SetActorHiddenInGame(false);
		this->SetActorEnableCollision(true);
		//IsEnabled = true;
	}
}

void AWall::DeactivateWallAndFloor()
{
	for (int i = 0; i < GM->WallList.Num(); i++)
	{
		if (GM->WallList[i]->RemovableWall)
		{
			GM->WallList[i]->EnableObject(false);
		}
	}
}

void AWall::AssignFloorLevel()
{

	for (int i = 0; i <= GM->FloorList.Num() -1; i++)
	{
		for (int j = 0; j < GM->WallList.Num(); j++)
		{
			if (GM->WallList[j]->WallDirection == WallPosition::Left && GM->WallList[j]->GetActorLocation().Y == GM->FloorList[i]->GetActorLocation().Y)
			{
				GM->FloorList[i]->LeftSide = GM->WallList[j]->GetActorLocation();
			}
			else if (GM->WallList[j]->WallDirection == WallPosition::Right && GM->WallList[j]->GetActorLocation().Y - 2230 == GM->FloorList[i]->GetActorLocation().Y)
			{
				GM->FloorList[i]->RightSide = GM->WallList[j]->GetActorLocation();

			}
		}

		for (auto Emp : GM->EmployeeList)
		{
			if (Emp->FloorLevel == -1)
			{
				if (Emp->GetActorLocation().Y > GM->FloorList[i]->LeftSide.Y && Emp->GetActorLocation().Y < GM->FloorList[i]->RightSide.Y)
				{
					Emp->FloorLevel = GM->FloorList[i]->FloorLevel;
				}
			}
		}

		for (auto OfficeDep : GM->OfficeDepartmentList)
		{
			if (OfficeDep->FloorLevel == -1)
			{
				if (OfficeDep->GetActorLocation().Y > GM->FloorList[i]->LeftSide.Y && OfficeDep->GetActorLocation().Y < GM->FloorList[i]->RightSide.Y)
				{
					OfficeDep->FloorLevel = GM->FloorList[i]->FloorLevel;
				}
			}
		}

		for (auto Workstation : GM->WorkstationList)
		{
			if (Workstation->FloorLevel == -1)
			{
				if (Workstation->GetActorLocation().Y > GM->FloorList[i]->LeftSide.Y && Workstation->GetActorLocation().Y < GM->FloorList[i]->RightSide.Y)
				{
					Workstation->FloorLevel = GM->FloorList[i]->FloorLevel;
				}
			}
			
		}

		for (auto Door : GM->DoorList)
		{
			if (Door->FloorLevel == -1)
			{
				if (Door->GetActorLocation().Y > GM->FloorList[i]->LeftSide.Y && Door->GetActorLocation().Y < GM->FloorList[i]->RightSide.Y)
				{
					Door->FloorLevel = GM->FloorList[i]->FloorLevel;
				}
			}

		}


	}



}
