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

	if (!Hire_ProgSup_Btn->OnClicked.IsBound())
	{
		Hire_ProgSup_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallProgrammerSupSpawn);
	}
	if (!Hire_ArtistSup_Btn->OnClicked.IsBound())
	{
		Hire_ArtistSup_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallArtistSupSpawn);
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
		if (GM->Money >= 10000) //make money editable inspector constant that scales up , same for all dep & sup hire
		{
			GM->Money -= 10000;
			ActivateWorkstation(ERole::Programmer);
			OfficeDepartment->GenerateActor(0, ERole::Programmer);
		}
	}
}

void UCeoDepMenuWidget::CallProgrammerSupSpawn()
{
	if (!GM->ProgrammingDepartment->HasSupervisor && GM->Money >= 30000) {
		GM->Money -= 30000;
		GM->ProgrammingDepartment->HasSupervisor = true;
		OfficeDepartment->GenerateActor(2, ERole::Programmer);
		Hire_ProgSup_Btn->SetIsEnabled(false);
		//OfficeDepartment->GetDepartmentUIValues();
	}
}

void UCeoDepMenuWidget::CallArtistSupSpawn()
{
	if (!GM->ArtistDepartment->HasSupervisor && GM->Money >= 30000) {
		GM->Money -= 30000;
		GM->ArtistDepartment->HasSupervisor = true;
		OfficeDepartment->GenerateActor(2, ERole::Artist);
		Hire_ArtistSup_Btn->SetIsEnabled(false);
		//OfficeDepartment->GetDepartmentUIValues();
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
			ActivateWorkstation(ERole::Artist);
			OfficeDepartment->GenerateActor(1, ERole::Artist);
		}
	}
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(3, ERole::Artist);
}

void UCeoDepMenuWidget::ActivateWorkstation(ERole StationRole)
{
	int Length = GM->WorkstationList.Num();

	for (int i = 0; i < Length; i++)
	{
		if (!GM->WorkstationList[i]->IsEnabled && GM->WorkstationList[i]->StationRole == StationRole)
		{
			GM->WorkstationList[i]->EnableStation(true);
			return;
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