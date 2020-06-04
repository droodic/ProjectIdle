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
#include "IdeaButton.h"

void UIdeaBacklogWidget::DisplayNewIdea(Idea* idea) {

	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, "Displaying new idea");
	//newIdea = idea;

	//idea->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	//AddValuesToButton(idea);

	//IdeaButtonList.Add(idea->IdeaButton);
	//IdeaScrollBox->AddChild(idea->IdeaButton);
	
	//if (!idea->IdeaButton->IdeaButton->OnClicked.IsBound())
	//{
	//	idea->IdeaButton->IdeaButton->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::SetIdeaCallMeeting);
	//}

	/*auto NewButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	AddValuesToButton(idea);
	idea->IdeaButton = NewButton;
	IdeaButtonList.Add(NewButton);
	IdeaScrollBox->AddChild(NewButton);
	*/

	if (!IdeaButton1->IsVisible() && OfficeDepartment->Index == 0)
	{
		IdeaButton1->SetVisibility(ESlateVisibility::Visible);
		IdeaButton1->SetRenderOpacity(1);
	}
	else if (!IdeaButton2->IsVisible() && OfficeDepartment->Index == 1)
	{
		IdeaButton2->SetVisibility(ESlateVisibility::Visible);
		IdeaButton2->SetRenderOpacity(1);
	}
	else if (!IdeaButton3->IsVisible() && OfficeDepartment->Index == 2)
	{
		IdeaButton3->SetVisibility(ESlateVisibility::Visible);
		IdeaButton3->SetRenderOpacity(1);
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

void UIdeaBacklogWidget::GetIdea(Idea* newIdea)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::FromInt(OfficeDepartment->Index));

	if (OfficeDepartment->Index == 0)
	{
		I_GameCover->SetColorAndOpacity(newIdea->CoverColor);

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
		I_GameCover_2->SetColorAndOpacity(newIdea->CoverColor);

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
		I_GameCover_3->SetColorAndOpacity(newIdea->CoverColor);


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

/*
void UIdeaBacklogWidget::AddValuesToButton(Idea* idea)
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
}*/

void UIdeaBacklogWidget::CallMeeting()
{
	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
		GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "populate GM");
	}

	//for (size_t i = 0; i < OfficeDepartment->Index; i++)
	//{
	//	IdeaButtonList[i]->IdeaButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	//	IdeaButtonList[i]->SetRenderOpacity(0.3);
	//}

	//Quick way to disable chosen idea button after calling meeting with it, need cleaner approach
	if (OfficeDepartment->Index - 1 == 0) {
		IdeaButton1->SetVisibility(ESlateVisibility::HitTestInvisible);
		IdeaButton1->SetRenderOpacity(0.3);
	}
	else if (OfficeDepartment->Index - 1 == 1) {
		IdeaButton2->SetVisibility(ESlateVisibility::HitTestInvisible);
		IdeaButton2->SetRenderOpacity(0.3);
	}
	else if (OfficeDepartment->Index - 1 == 2) {
		IdeaButton3->SetVisibility(ESlateVisibility::HitTestInvisible);
		IdeaButton3->SetRenderOpacity(0.3);
	}

	GM->MeetingDepartment->MoveToMeeting();
	SendIdea();

}

/*UFUNCTION() void UIdeaBacklogWidget::SetIdeaCallMeeting()
{
	ChosenIndex = 0;
	CallMeetingBtn->SetIsEnabled(true);
}*/

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
	/*else if (newIdea == nullptr) {
		GEngine->AddOnScreenDebugMessage(106, 5.f, FColor::Red, "newIdea null");
	}*/
}
