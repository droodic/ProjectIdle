// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine.h"
#include "WorkstationUpgradeWidget.h"

void UWorkstationUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!UpgradeMonitor_Btn->OnClicked.IsBound())
	{
		UpgradeMonitor_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Monitor);
	}
}

void UWorkstationUpgradeWidget::Monitor()
{
	if (Station != nullptr)
	{
		Station->UpgradeMesh(0);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Jeff Noob");
	}

}