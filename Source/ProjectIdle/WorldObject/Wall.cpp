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
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Wall = this;
	//UpdateWallMaterialTest();
	//UpdateWallMaterial(Material);
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

