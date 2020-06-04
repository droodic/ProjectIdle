// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Components/Button.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/GameManager.h"
#include "OfficeDepartment.h"
#include "ProjectIdle/Workstation.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
#include "Engine.h"
#include "Widgets/IdeaButton.h"
#include "Blueprint/UserWidget.h"

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
	if (GM->Money >= 10000) {
		GM->Money -= 10000;
		ActiveWorkstation(0);
		OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 0);
	}
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	if (GM->Money >= 10000) {
		GM->Money -= 10000;
		ActiveWorkstation(1);
		OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 1);
	}
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 3);
}

void UCeoDepMenuWidget::ActiveWorkstation(int Number)
{
	int32 length = GM->WorkstationList.Num();
	int32 employeeSize = GM->EmployeeList.Num();
	int32 ActiveStation = GM->WorkStation->WorkstationActiveLenght();
	
	if (ActiveStation <= employeeSize)
	{
		for (int i = 0; i < length; i++)
		{
			if (Number == 0)
			{
				if (GM->WorkstationList[i]->DisableObject && GM->WorkstationList[i]->IsA(AProgrammerStation::StaticClass()))
				{
					//GM->WorkstationList[i]->IsObjectDisable = false;
					//GM->WorkstationList[i]->DisableStation(false);
					GM->WorkstationList[i]->DisableObject = false;
					//To leave the function once one if found.
					return;
				}
			}
			if (Number == 1)
			{
				if (GM->WorkstationList[i]->DisableObject && GM->WorkstationList[i]->IsA(AArtistStation::StaticClass()))
				{
					//GM->WorkstationList[i]->IsObjectDisable = false;
					//GM->WorkstationList[i]->DisableStation(false);
					GM->WorkstationList[i]->DisableObject = false;
					//To leave the function once one if found.
					return;
				}
			}
		}
	}
}

void UCeoDepMenuWidget::GetIdea(Idea* idea)
{
	auto NewButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));

	AddValuesToButton(NewButton, idea);
	IdeaButtonList.Add(NewButton);
	IdeaScrollBox->AddChild(NewButton);
	
	//if (NewButton != nullptr)
	//{
	//	AddValuesToButton(NewButton, idea);
	//	IdeaScrollBox->AddChild(NewButton);
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Red, "IdeaButton == nullptr");
	//}
	
}

void UCeoDepMenuWidget::AddValuesToButton(UIdeaButton* button, Idea* idea)
{
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, "Values Added to button");

	button->GameCover_I->SetColorAndOpacity(idea->CoverColor);

	button->GameTitle_T->SetText(FText::FromString(idea->IdeaName));
	button->GameDescription_T->SetText(FText::FromString(idea->IdeaDescription));
	button->Genre_T->SetText(Idea::GenreToText(idea->Genre));
	button->SuccessChance_T->SetText(FText::AsPercent(idea->SuccessChance / 100.f));

	button->Weight_T->SetText((idea->ProgrammerWorkload > idea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

	if (idea->ProgrammerWorkload == idea->ArtistWorkload)
	{
		button->Weight_T->SetText(FText::FromString("All"));
	}
}