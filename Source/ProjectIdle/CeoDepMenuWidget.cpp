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
	ActiveWorkstation(0);
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 0);
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	ActiveWorkstation(1);
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 1);
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 3);
}

void UCeoDepMenuWidget::ActiveWorkstation(int Number)
{
	int32 length = GM->WorkstationList.Num();

	for (int i = 0; i < length; i++)
	{
		if (Number == 0)
		{
			if (GM->WorkstationList[i]->DisableObject && GM->WorkstationList[i]->IsA(AProgrammerStation::StaticClass()))
			{
				GM->WorkstationList[i]->DisableStation(false);
				//To leave the function once one if found.
				return;
			}
		}
		if (Number == 1)
		{
			if (GM->WorkstationList[i]->DisableObject && GM->WorkstationList[i]->IsA(AArtistStation::StaticClass()))
			{
				GM->WorkstationList[i]->DisableStation(false);
				//To leave the function once one if found.
				return;
			}
		}
		
	}
}