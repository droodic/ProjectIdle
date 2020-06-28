// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "ProjectIdle/GameManager.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"


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
	if (this->Type == ObjectType::Floor)
	{
		GM->FloorList.Add(this);
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
