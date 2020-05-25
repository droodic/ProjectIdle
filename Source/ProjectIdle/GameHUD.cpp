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
		MoneyWidget = CreateWidget<UMoneyWidget>(UGameplayStatics::GetPlayerController(this, 0), MoneyWidgetClass);
		if (MoneyWidget)
		{
			MoneyWidget->AddToViewport();
		}
	}
	if (EmployeeSheetClass)
	{
		EmpSheetWidget = CreateWidget<UEmployeeSheetWidget>(UGameplayStatics::GetPlayerController(this, 0), EmployeeSheetClass);
	}
}

void AGameHUD::ShowEmployeeSheet(class AEmployee* emp)
{

	if (!EmpSheetWidget->IsInViewport())
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Showing Employee Sheet"));
		EmpSheetWidget->Morale = emp->Morale;
		EmpSheetWidget->Salary = emp->Salary;
		EmpSheetWidget->EmployeeRole = emp->EmployeeRole;
		EmpSheetWidget->AddToViewport();

	}

	else if (EmpSheetWidget->IsInViewport()) {
		EmpSheetWidget->RemoveFromViewport();
		//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Showing New Employee Sheet"));
		//EmpSheetWidget->Morale = emp->Morale;
		//EmpSheetWidget->Salary = emp->Salary;
		//EmpSheetWidget->EmployeeRole = emp->EmployeeRole;
	}

}

//template<class T>
void AGameHUD::ShowWidget(UUserWidget* Widgetc, TSubclassOf<UUserWidget> WidgetClass)
{
	//auto UseClass = Widgetc;
		//Widgetc->RemoveFromViewport();
	if (Widgetc != nullptr && Widgetc->IsValidLowLevel()) {
		Widgetc->AddToViewport();
	}
	else {
		auto NewWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), WidgetClass);
		NewWidget->AddToViewport();
	}

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