// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UIdeaBacklogWidget::DisplayNewIdea() {

	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, "Displaying new idea");

	if (!IdeaButton1->IsVisible())
	{
		IdeaButton1->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!IdeaButton2->IsVisible())
	{
		IdeaButton2->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!IdeaButton3->IsVisible())
	{
		IdeaButton3->SetVisibility(ESlateVisibility::Visible);
	}
}

void UIdeaBacklogWidget::Back()
{
	GEngine->AddOnScreenDebugMessage(12039, 5.f, FColor::Green, "Idea1");
	OfficeDepartment->Back();
}

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (!Back_Btn->OnClicked.IsBound())
	{
		Back_Btn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::Back);
	}
}

void UIdeaBacklogWidget::GetIdea(Idea* idea)
{
	newIdea = idea;

	if (!IdeaButton1->IsVisible())
	{
		T_GameTitle->SetText(FText::FromString("TEST GAME"));
		T_GameDescription->SetText(FText::FromString("Game Description"));

		T_SuccessChance->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight->SetText(FText::FromString("All"));
		}
	}
	else if (!IdeaButton2->IsVisible())
	{
		T_GameTitle_2->SetText(FText::FromString("TEST GAME"));
		T_GameDescription_2->SetText(FText::FromString("Game Description"));

		T_SuccessChance_2->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight_2->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight_2->SetText(FText::FromString("All"));
		}
	}
	else if (!IdeaButton3->IsVisible())
	{
		T_GameTitle_3->SetText(FText::FromString("TEST GAME"));
		T_GameDescription_3->SetText(FText::FromString("Game Description"));

		T_SuccessChance_3->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight_3->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight_3->SetText(FText::FromString("All"));
		}
	}
}


void UIdeaBacklogWidget::SendIdea()
{
	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
		GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "populate GM");
	}

	if (GM->MeetingDepartment == nullptr) {
		GEngine->AddOnScreenDebugMessage(102, 5.f, FColor::Red, "GM->MeetingDepartment is null");
	}

	else if (GM->MeetingDepartment != nullptr) {
		GM->MeetingDepartment->TakeIdea(newIdea);
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Meeting TakeIdea");

	}
}



