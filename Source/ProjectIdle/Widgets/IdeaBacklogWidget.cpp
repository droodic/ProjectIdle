// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"



void UIdeaBacklogWidget::DisplayNewIdea() {

	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, "Displaying new idea");

	if (/*!IdeaButton1->IsVisible()*/OfficeDepartment->Index == 0)
	{
		IdeaButton1->SetVisibility(ESlateVisibility::Visible);
	}
	else if(/*!IdeaButton2->IsVisible()*/OfficeDepartment->Index == 1)
	{
		IdeaButton2->SetVisibility(ESlateVisibility::Visible);
	}
	else if(/*!IdeaButton3->IsVisible()*/OfficeDepartment->Index == 2)
	{
		IdeaButton3->SetVisibility(ESlateVisibility::Visible);
	}
}

void UIdeaBacklogWidget::Back()
{
	OfficeDepartment->Back();
}

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();

	//GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!Back_Btn->OnClicked.IsBound())
	{
		Back_Btn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::Back);
	}
	if (!CallMeetingBtn->OnClicked.IsBound())
	{
		CallMeetingBtn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::CallMeeting);
	}
}

void UIdeaBacklogWidget::GetIdea(Idea* idea)
{
	newIdea = idea;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::FromInt(OfficeDepartment->Index -1));

	if (OfficeDepartment->Index == 0)
	{
		I_GameCover->SetColorAndOpacity(FLinearColor::MakeRandomColor());

		/*T_GameTitle->SetText(FText::FromString("TEST GAME"));
		T_GameDescription->SetText(FText::FromString("Game Description of game 1"));
		*/

		T_GameTitle->SetText(FText::FromString(newIdea->IdeaName));
		T_GameDescription->SetText(FText::FromString(newIdea->IdeaDescription));
		
		T_Genre->SetText(Idea::GenreToText(newIdea->Genre));
		
		T_SuccessChance->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));
		
		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight->SetText(FText::FromString("All"));
		}
	}
	else if (OfficeDepartment->Index == 1)
	{
		I_GameCover_2->SetColorAndOpacity(FLinearColor::MakeRandomColor());

		/*
		T_GameTitle_2->SetText(FText::FromString("TEST GAME 2"));
		T_GameDescription_2->SetText(FText::FromString("Game Description of game 2"));
		*/

		T_GameTitle_2->SetText(FText::FromString(newIdea->IdeaName));
		T_GameDescription_2->SetText(FText::FromString(newIdea->IdeaDescription));

		T_Genre_2->SetText(Idea::GenreToText(newIdea->Genre));

		T_SuccessChance_2->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight_2->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight_2->SetText(FText::FromString("All"));
		}
	}
	else if (OfficeDepartment->Index == 2)
	{
		I_GameCover_3->SetColorAndOpacity(FLinearColor::MakeRandomColor());
		
		/*
		T_GameTitle_3->SetText(FText::FromString("TEST GAME 3"));
		T_GameDescription_3->SetText(FText::FromString("Game Description of game 3"));
		*/
		
		T_GameTitle_3->SetText(FText::FromString(newIdea->IdeaName));
		T_GameDescription_3->SetText(FText::FromString(newIdea->IdeaDescription));

		T_Genre_3->SetText(Idea::GenreToText(newIdea->Genre));
		
		T_SuccessChance_3->SetText(FText::AsPercent(newIdea->SuccessChance / 100.f));

		T_Weight_3->SetText((newIdea->ProgrammerWorkload > newIdea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

		if (newIdea->ProgrammerWorkload == newIdea->ArtistWorkload)
		{
			T_Weight_3->SetText(FText::FromString("All"));
		}
	}
}

void UIdeaBacklogWidget::CallMeeting()
{

	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
		GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "populate GM");
	}
	GM->MeetingDepartment->MoveToMeeting();
	SendIdea();

}

//Called by CallMeeting
void UIdeaBacklogWidget::SendIdea() {

	
	//Gm populated in CallMeeting
	if (GM->MeetingDepartment == nullptr) {
		GEngine->AddOnScreenDebugMessage(102, 5.f, FColor::Red, "GM->MeetingDepartment is null");
	}
	else if (GM->MeetingDepartment != nullptr) {
		auto tIdea = OfficeDepartment->IdeaList[ChosenIndex];
		if (tIdea != nullptr) {
			GEngine->AddOnScreenDebugMessage(1036, 5.f, FColor::Red, "tIdea work");
			GM->MeetingDepartment->TakeIdea(tIdea);
		}
		//GM->MeetingDepartment->TakeIdea(OfficeDepartment->IdeaList[ChosenIndex]);
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Meeting TakeIdea");
	}
	else if (newIdea == nullptr) {
		GEngine->AddOnScreenDebugMessage(106, 5.f, FColor::Red, "newIdea null");
	}
}
