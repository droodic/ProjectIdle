// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Components/Button.h"
#include "ProjectIdle/GameManager.h"
#include "OfficeDepartment.h"
#include "ProjectIdle/Workstation.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
#include "Engine.h"

void UCeoDepMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//AddToRoot();
	GM = GetWorld()->GetGameInstance<UGameManager>();

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
	ActiveWorkstation();
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 1);
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 3);
}

void UCeoDepMenuWidget::ActiveWorkstation()
{
	int32 length = GM->WorkstationList.Num();

	for (int i = 0; i < length; i++)
	{
		
		if (GM->WorkstationList[i]->DisableObject)
		{
			GM->WorkstationList[i]->DisableStation(false);
			//To leave the function once one if found.
			return;
		}
	}
}