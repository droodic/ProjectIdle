#include "Door.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Employees/Employee.h"
#include "Components/MeshComponent.h"

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


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Door = this;
	GM->DoorList.Add(this);
	//DoorLocation = this->GetActorLocation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Fire Employee
void ADoor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto Emp = Cast<AEmployee>(OtherActor);

	if (Emp != nullptr && Emp->IsFired)
	{
		Emp->FiredFinal();
		//UI->ShowWidget(OfficeDepMenuWidget, UserWidgets[1]); 
	}
}

