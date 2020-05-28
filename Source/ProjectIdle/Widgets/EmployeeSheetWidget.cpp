// Fill out your copyright notice in the Description page of Project Settings.


#include "EmployeeSheetWidget.h"
#include "ProjectIdle/Employees/Employee.h"

void UEmployeeSheetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (!Promote_Btn->OnClicked.IsBound())
	{
		Promote_Btn->OnClicked.AddDynamic(this, &UEmployeeSheetWidget::Promote);
	}
	if (!Fire_Btn->OnClicked.IsBound())
	{
		Fire_Btn->OnClicked.AddDynamic(this, &UEmployeeSheetWidget::Fire);
	}*/
}

void UEmployeeSheetWidget::Promote()
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, TEXT("Promote button pressed"));
	Employee->Promote();
}

void UEmployeeSheetWidget::Fire()
{
	Employee->Fire();
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
	case EPosition::Programmer:
		text = FText::FromString("Programmer");
		break;
	case EPosition::SeniorProgrammer:
		text = FText::FromString("Senior");
		break;
	}

	return text;
}