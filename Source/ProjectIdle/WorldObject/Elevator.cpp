// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "ProjectIdle/GameManager.h"
#include "Components/MeshComponent.h"
#include "ProjectIdle/Widgets/ElevatorWidget.h"
#include "ProjectIdle/ProjectIdleCharacter.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	ElevatorMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	CollisionBox->AttachTo(ElevatorMesh);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Elevator = this;

	if (StartingElevator)
	{
		GM->ElevatorList.Add(this);
	}
	else
	{
		GM->UnassignedElevatorList.Add(this);
	}

	UWorld* world = GetWorld();
	if (UserWidget != nullptr)
	{
		ElevatorWidget = CreateWidget<UElevatorWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidget);
	}
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AElevator::OnInteract()
{
	//if (!ElevatorWidget->IsInViewport())
	//{
	//	ElevatorWidget->AddToViewport();
	//}
	//else
	//{
	//	ElevatorWidget->RemoveFromParent();
	//}
}



void AElevator::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto Player = Cast<AProjectIdleCharacter>(OtherActor);

	if (Player != nullptr && GM->IsFloorUpgraded)
	{
		if (Player->CurrentFloor == 1)
		{
			GM->Character->PlayerControl->PlayerCameraManager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, true, true);
			Player->SetActorLocation(GM->ElevatorList[1]->SpawnPoint->GetComponentLocation());
			Player->CurrentFloor = 2;
			//UI->MoneyWidget->ShowANotification("Welcome to Floor 2");
			return;
		}

		if (Player->CurrentFloor == 2)
		{
			GM->Character->PlayerControl->PlayerCameraManager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, true, true);
			Player->SetActorLocation(GM->ElevatorList[0]->SpawnPoint->GetComponentLocation());
			Player->CurrentFloor = 1;
			//UI->MoneyWidget->ShowANotification("Welcome to Floor 1");
			return;
		}
	}
}

void AElevator::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr && ElevatorWidget->IsInViewport())
	{
		//ElevatorWidget->RemoveFromViewport();
	}
}

