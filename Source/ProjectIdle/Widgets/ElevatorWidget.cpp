// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/WorldObject/Elevator.h"
#include "ProjectIdle/Widgets/ElevatorWidget.h"
#include "ProjectIdle/GameHUD.h"

void UElevatorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->ElevatorWidget = this;
}