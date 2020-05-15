// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

AGameHUD::AGameHUD()
{

}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MoneyWidgetClass)
	{
		MoneyWidget = CreateWidget<UMoneyWidget>(GetWorld(), MoneyWidgetClass);
		if (MoneyWidget)
		{
			MoneyWidget->AddToViewport();
		}
	}
	if (EmployeeSheetClass)
	{
		//EmpSheetWidget = CreateWidget<UEmployeeSheetWidget>(GetWorld(), EmployeeSheetClass);
	}
}

void AGameHUD::ShowEmployeeSheet(class AEmployee* emp) 
{
	EmpSheetWidget->Morale = emp->Morale;
	EmpSheetWidget->Salary = emp->Salary;
	EmpSheetWidget->EmployeeRole = emp->EmployeeRole;
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::UpdateMoney(int32 Value)
{
	if (MoneyWidget)
	{
		MoneyWidget->UpdateMoney(Value);
	}
}