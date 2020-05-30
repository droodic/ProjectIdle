// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Components/Button.h"
#include "OfficeDepartment.h"
#include "Engine.h"

void UCeoDepMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//AddToRoot();

	if (!Hire_Prog_Btn->OnClicked.IsBound())
	{
	    Hire_Prog_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallProgrammerSpawn);
	}
	if (!Hire_Artist_Btn->OnClicked.IsBound())
	{
		Hire_Artist_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallArtistSpawn);
	}
}

void UCeoDepMenuWidget::CallProgrammerSpawn()
{
	OfficeDepartment->HireEmployee(OfficeDepartment->SpawnWorker, 0);
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	OfficeDepartment->HireEmployee(OfficeDepartment->SpawnWorker, 1);
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	//OfficeDepartment->HireEmployee(OfficeDepartment->SpawnWorker, 0);
}