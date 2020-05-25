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
	
}

// Called every frame
void AWorkstation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

