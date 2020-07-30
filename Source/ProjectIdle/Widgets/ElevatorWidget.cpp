// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/WorldObject/Elevator.h"
#include "ProjectIdle/Widgets/ElevatorWidget.h"
#include "ProjectIdle/GameHUD.h"
#include "ProjectIdle/ProjectIdleCharacter.h"
#include "Kismet/GameplayStatics.h"

void UElevatorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	Player = Cast<AProjectIdleCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	GM->ElevatorWidget = this;


	if (!Btn_Floor_1->OnClicked.IsBound())
	{
		Btn_Floor_1->OnClicked.AddDynamic(this, &UElevatorWidget::MoveToFloorOne);
	}

	if (!Btn_Floor_2->OnClicked.IsBound())
	{
		Btn_Floor_2->OnClicked.AddDynamic(this, &UElevatorWidget::MoveToFloorTwo);
	}

	if (!Btn_Floor_3->OnClicked.IsBound())
	{
		Btn_Floor_3->OnClicked.AddDynamic(this, &UElevatorWidget::MoveToFloorThree);
	}
}


void UElevatorWidget::MoveToFloorOne()
{

	if (GM->Character) {
		GM->Character->SetActorLocation(GM->ElevatorList[0]->SpawnPoint->GetComponentLocation());
		GM->Character->CurrentFloor = 1;
	}
}

void UElevatorWidget::MoveToFloorTwo()
{
	if (GM->Character) {
		if (GM->ElevatorList.Num() >= 2 && GM->ElevatorList[1]->FloorLevel == 2) {
			GM->Character->CurrentFloor = 2;
			GM->Character->SetActorLocation(GM->DoorList[1]->SpawnPoint->GetComponentLocation());
			//GM->Character->SetActorLocation(GM->ElevatorList[GM->Character->CurrentFloor - 1]->SpawnPoint->GetComponentLocation());
		}
	}
}

void UElevatorWidget::MoveToFloorThree()
{
	if (GM->Character) {
		if (GM->ElevatorList.Num() >= 3) {
			GM->Character->SetActorLocation(GM->ElevatorList[2]->SpawnPoint->GetComponentLocation());
			GM->Character->CurrentFloor = 3;
		}
	}
}