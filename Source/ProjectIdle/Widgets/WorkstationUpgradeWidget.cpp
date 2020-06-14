// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkstationUpgradeWidget.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"



void UWorkstationUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!UpgradeMonitor_Btn->OnClicked.IsBound())
	{

		UpgradeMonitor_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Monitor);
	}

	if (!UpgradeKeyboard_Btn->OnClicked.IsBound())
	{
		UpgradeKeyboard_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Keyboard);
	}
}

void UWorkstationUpgradeWidget::Monitor()
{
	if (Station)
	{
		Station->UpgradeMesh(0);
	}
}

void UWorkstationUpgradeWidget::Keyboard()
{
	if (Station)
	{
		Station->UpgradeMesh(1);
	}
}