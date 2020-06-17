// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkstationUpgradeWidget.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"



void UWorkstationUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!Monitor_Btn->OnClicked.IsBound())
	{
		Monitor_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryMonitor);
	}

	if (!Desk_Btn->OnClicked.IsBound())
	{
		Desk_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryDesk);
	}


	if (!Chair_Btn->OnClicked.IsBound())
	{

		Chair_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Monitor);
	}

	if (!UpgradeKeyboard_Btn->OnClicked.IsBound())
	{
		UpgradeKeyboard_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Keyboard);
	}
}


void UWorkstationUpgradeWidget::ShowInventory(ECategory ItemCategory) {

}


void UWorkstationUpgradeWidget::ShowInventoryMonitor() {
	ShowInventory(ECategory::ComputerComponents);
}


void UWorkstationUpgradeWidget::ShowInventoryDesk() {

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