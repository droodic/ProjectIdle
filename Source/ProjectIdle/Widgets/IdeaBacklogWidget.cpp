// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
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



	//IdeaButton1->SetVisibility(ESlateVisibility::Hidden);
	//IdeaButton2->SetVisibility(ESlateVisibility::Hidden);
	//IdeaButton3->SetVisibility(ESlateVisibility::Hidden); //array?
}

void UIdeaBacklogWidget::GetIdea(Idea* idea) 
{
	newIdea = idea;
	T_GameTitle->SetText(FText::FromString("TEST GAME"));
	T_GameDescription->SetText(FText::FromString("Game Description"));

	//->SetText(UEnum::GetDisplayNameTextByValue(2));

	T_SuccessChance->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

	T_Weight->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

	if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
	{
		T_Weight->SetText(FText::FromString("All"));
	}
}