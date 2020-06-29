// Fill out your copyright notice in the Description page of Project Settings.


#include "EmployeeSheetWidget.h"
#include "ProjectIdle/Employees/Supervisor.h"
#include "ProjectIdle/Employees/FloorManager.h"

void UEmployeeSheetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Promote_Btn->OnClicked.IsBound())
	{
		Promote_Btn->OnClicked.AddDynamic(this, &UEmployeeSheetWidget::Promote);
	}
	if (!Fire_Btn->OnClicked.IsBound())
	{
		Fire_Btn->OnClicked.AddDynamic(this, &UEmployeeSheetWidget::Fire);
	}
	if (!Action_Btn->OnClicked.IsBound())
	{
		Action_Btn->OnClicked.AddDynamic(this, &UEmployeeSheetWidget::PerformAction);
	}
}

void UEmployeeSheetWidget::Promote()
{
	if (Employee != nullptr)
	{
		Employee->Promote();
	}
}

void UEmployeeSheetWidget::Fire()
{
	if (Employee != nullptr)
	{
		Employee->Fire();
	}
}

void UEmployeeSheetWidget::PerformAction()
{
	if (Employee != nullptr)
	{
		if (Cast<ASupervisor>(Employee) != nullptr) {
			Cast<ASupervisor>(Employee)->EvaluateEmployee();
		}
		else if (Cast<AFloorManager>(Employee) != nullptr) {
			Cast<AFloorManager>(Employee)->AutomateTasks();
		}
	}
}

FText UEmployeeSheetWidget::RoleToText(ERole role)
{
	FText text;

	switch (role)
	{
	case ERole::Programmer:
		text = FText::FromString("Programmer");
		break;
	case ERole::Artist:
		text = FText::FromString("Artist");
		break;

	}

	return text;
}

FText UEmployeeSheetWidget::PositionToText(EPosition position)
{
	FText text;

	switch (position)
	{
	case EPosition::Intern:
		text = FText::FromString("Intern");
		break;
	case EPosition::Junior:
		text = FText::FromString("Junior");
		break;
	case EPosition::Regular:
		text = FText::FromString("Regular");
		break;
	case EPosition::Senior:
		text = FText::FromString("Senior");
		break;
	case EPosition::Supervisor:
		text = FText::FromString("Supervisor");
		break;
	}

	return text;
}

FText UEmployeeSheetWidget::SalaryToText(float salar)
{
	return FText::AsCurrency(salar);
}
