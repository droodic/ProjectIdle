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

	idea->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	AddValuesToButton(idea);

	IdeaScrollBox->AddChild(idea->IdeaButton);
}

void UIdeaBacklogWidget::Back()
{
	OfficeDepartment->Back();
	CallMeetingBtn->SetIsEnabled(false);
}

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (!Back_Btn->OnClicked.IsBound())
	{
		Back_Btn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::Back);
	}
	if (!CallMeetingBtn->OnClicked.IsBound())
	{
		CallMeetingBtn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::CallMeeting);
	}
}

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

	idea->IdeaButton->BacklogWidget = this;
	idea->IdeaButton->OfficeDepartment = OfficeDepartment;

	idea->IdeaButton->storedIndex = OfficeDepartment->Index;
}

void UIdeaBacklogWidget::CallMeeting()
{
	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
		GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "populate GM");
	}

	OfficeDepartment->IdeaList[ChosenIndex]->IdeaButton->IdeaButton->SetIsEnabled(false);
	//UIdeaButton::IsInProduction = true;
	GM->IdeaInProduction = true;
	CallMeetingBtn->SetIsEnabled(false);

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
		if (tIdea != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(1036, 5.f, FColor::Red, "tIdea work");
			GM->MeetingDepartment->TakeIdea(tIdea);
		}
		//GM->MeetingDepartment->TakeIdea(OfficeDepartment->IdeaList[ChosenIndex]);
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Meeting TakeIdea");
	}
}
