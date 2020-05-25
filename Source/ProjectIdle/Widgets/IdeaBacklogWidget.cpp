// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ProjectIdle/Idea.h"


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

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UIdeaBacklogWidget::GetIdea(Idea* idea)
{
	newIdea = idea;
	T_GameTitle->SetText(FText::FromString("TEST GAME"));
	T_GameDescription->SetText(FText::FromString("Game Description"));

	T_SuccessChance->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

	T_Weight->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

	if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
	{
		T_Weight->SetText(FText::FromString("All"));
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



