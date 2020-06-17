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
	//Show computercomponents 
	for (auto Item : GM->InventoryList) {
		if (Item->ItemCategory == ECategory::ComputerComponents) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Item :" + Item->ItemName);
		}

	}
}


void UWorkstationUpgradeWidget::ShowInventoryMonitor() {
	ShowInventory(ECategory::ComputerComponents);
}


void UWorkstationUpgradeWidget::ShowInventoryDesk() {
	ShowInventory(ECategory::DeskAndChairs);
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