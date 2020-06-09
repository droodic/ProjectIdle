// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Idea.h"
#include "GameManager.h"
#include "OfficeDepartment.h"
#include "Workstation.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/IdeaButton.h"
#include "Components/Button.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"

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
	if (!PublishGame_Btn->OnClicked.IsBound())
	{
		PublishGame_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::PublishGame);
	}
}

void UCeoDepMenuWidget::CallProgrammerSpawn()
{
	int32 length = GM->WorkstationList.Num();
	int32 numberOfProgrammerStation = 0;
	int32 numberOfArtistStation = 0;

	for (int i = 0; i < length; i++)
	{
		if (GM->WorkstationList[i]->IsA(AProgrammerStation::StaticClass()))
		{
			numberOfProgrammerStation++;
		}
	}

	if (numberOfProgrammerStation > GM->NumOfProgrammers)
	{
		if (GM->Money >= 10000)
		{
			GM->Money -= 10000;
			ActiveWorkstation(0);
			OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 0);
		}
	}
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	int32 length = GM->WorkstationList.Num();
	int32 numberOfProgrammerStation = 0;
	int32 numberOfArtistStation = 0;

	for (int i = 0; i < length; i++)
	{
		if (GM->WorkstationList[i]->IsA(AArtistStation::StaticClass()))
		{
			numberOfArtistStation++;
		}
	}
	if (numberOfArtistStation > GM->NumOfArtists)
	{
		if (GM->Money >= 10000)
		{
			GM->Money -= 10000;
			ActiveWorkstation(1);
			OfficeDepartment->GenerateActor(OfficeDepartment->SpawnActors, 1);
		}
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

void UCeoDepMenuWidget::PublishGame()
{
	PublishGame_Btn->SetIsEnabled(false);
	OfficeDepartment->PublishGame();
}

void UCeoDepMenuWidget::GetFinishedIdea(Idea* idea)
{
	idea->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	OfficeDepartment->FinishedIdeaList.Insert(idea, Index);
	AddValuesToButton(OfficeDepartment->FinishedIdeaList[Index]);
	
	IdeaScrollBox->AddChild(OfficeDepartment->FinishedIdeaList[Index]->IdeaButton);

	Index++;
}

void UCeoDepMenuWidget::AddValuesToButton(Idea* idea)
{
	idea->IdeaButton->GameCover_I->SetColorAndOpacity(idea->CoverColor);

	idea->IdeaButton->GameTitle_T->SetText(FText::FromString(idea->IdeaName));
	idea->IdeaButton->GameDescription_T->SetText(FText::FromString(idea->IdeaDescription));
	idea->IdeaButton->Genre_T->SetText(Idea::GenreToText(idea->Genre));
	idea->IdeaButton->SuccessChance_T->SetText(FText::AsPercent(idea->SuccessChance / 100.f));

	idea->IdeaButton->Weight_T->SetText((idea->ProgrammerWorkload > idea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

	if (idea->ProgrammerWorkload == idea->ArtistWorkload)
	{
		idea->IdeaButton->Weight_T->SetText(FText::FromString("All"));
	}

	idea->IdeaButton->BacklogWidget = OfficeDepartment->BacklogWidget;
	idea->IdeaButton->OfficeDepartment = OfficeDepartment;

	idea->IdeaButton->storedIndex = Index;
	idea->IdeaButton->IsFinished = true;
}