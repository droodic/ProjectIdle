// Fill out your copyright notice in the Description page of Project Settings.


#include "Department.h"
#include "GameManager.h"

// Sets default values
ADepartment::ADepartment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickableMesh"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	CollisionBox->AttachTo(BaseMesh);
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ADepartment::BeginPlay()
{
	Super::BeginPlay();
	//GM = GetWorld()->GetGameInstance<UGameManager>();
}



// Called every frame
void ADepartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

