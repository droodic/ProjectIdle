// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"
#include "GameManager.h"
#include "Components/MeshComponent.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->MeetingChairList.Add(this);
	ChairLocation = this->GetActorLocation();
	//UE_LOG(LogActor, Warning, TEXT("%s"), *ChairLocation.ToString())

}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

