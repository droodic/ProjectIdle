// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Components/Button.h"
#include "ProjectIdle/GameManager.h"
#include "OfficeDepartment.h"
#include "Workstation.h"
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
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 0);
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 1);
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 3);
}