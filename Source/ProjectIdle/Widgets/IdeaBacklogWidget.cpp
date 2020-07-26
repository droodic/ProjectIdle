// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/Employees/FloorManager.h"
#include "MeetingDepWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "IdeaButton.h"

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (!Back_Btn->OnClicked.IsBound())
	{
		Back_Btn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::Return);
	}
	if (!CallMeetingBtn->OnClicked.IsBound())
	{
		CallMeetingBtn->OnClicked.AddDynamic(this, &UIdeaBacklogWidget::CallMeeting);
	}
}

void UIdeaBacklogWidget::DisplayNewIdea(Idea* idea) {

	GM = GetWorld()->GetGameInstance<UGameManager>();

	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, "Displaying new idea");

	idea->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	AddValuesToButton(idea);

	IdeaScrollBox->AddChild(idea->IdeaButton);
	//GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->BacklogWidget->CallMeetingBtn->SetIsEnabled(true);

}

void UIdeaBacklogWidget::Return()
{
	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
		GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "populate GM");
	}

	//OfficeDepartment->BacklogReturn();
	GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->BacklogReturn();
	//GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->BacklogWidget->CallMeetingBtn->SetIsEnabled(false);

	//CallMeetingBtn->SetIsEnabled(false);
}

void UIdeaBacklogWidget::AddValuesToButton(Idea* idea)
{
	idea->IdeaButton->GameCover_I->SetColorAndOpacity(idea->CoverColor);

	idea->IdeaButton->GameTitle_T->SetText(FText::FromString(idea->IdeaName));
	idea->IdeaButton->GameDescription_T->SetText(FText::FromString(idea->IdeaDescription));
	idea->IdeaButton->Genre_T->SetText(Idea::GenreToText(idea->Genre));
	idea->IdeaButton->SuccessChance_T->SetText(FText::AsPercent(idea->SuccessChance / 100.f));

	if (idea->ProgrammerWorkload > (idea->ArtistWorkload + 20)) {
		idea->IdeaButton->Weight_T->SetText(FText::FromString("Programmer"));
	}
	else if (idea->ArtistWorkload > (idea->ProgrammerWorkload + 20)) {
		idea->IdeaButton->Weight_T->SetText(FText::FromString("Artist"));
	}
	else
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

	int	CurrentFloorLevel = GM->Character->CurrentFloor - 1;

		GM->OfficeDepartmentList[CurrentFloorLevel]->IdeaList[ChosenIndex]->IdeaButton->IdeaButton->SetIsEnabled(false);
		//OfficeDepartment->IdeaList[ChosenIndex]->IdeaButton->IdeaButton->SetIsEnabled(false);
		//UIdeaButton::IsInProduction = true;

		GM->IdeaInProduction = true;
		GM->OfficeDepartmentList[CurrentFloorLevel]->IdeaCurrentFloor = true;
	    
		GM->OfficeDepartmentList[CurrentFloorLevel]->BacklogWidget->CallMeetingBtn->SetIsEnabled(false);
		//CallMeetingBtn->SetIsEnabled(false);
		//GM->MeetingDepartment->MoveToMeeting();
		GM->MeetingDepartmentList[CurrentFloorLevel]->MoveToMeeting();
		SendIdea(ChosenIndex);

}
void UIdeaBacklogWidget::CallMeeting_M(AFloorManager* ManagerRef)
{
	if (GM == nullptr)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
	}
	GM->OfficeDepartmentList[0]->IdeaList[ManagerRef->IdeaIndex]->IdeaButton->IdeaButton->SetIsEnabled(false);
	//OfficeDepartment->IdeaList[ManagerRef->IdeaIndex]->IdeaButton->IdeaButton->SetIsEnabled(false);
	//UIdeaButton::IsInProduction = true;
	GM->IdeaInProduction = true;
	GM->OfficeDepartmentList[GM->FLoorM->FloorLevel - 1]->IdeaCurrentFloor = true;

	//CallMeetingBtn->SetIsEnabled(false);
	GM->MeetingDepartmentList[0]->MoveToMeeting();
	//GM->MeetingDepartment->MoveToMeeting();
	ManagerRef->MeetingState = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Movetomeeting");

	//ManagerRef->MoveEmployee();
	SendIdeaFloorM(ManagerRef->IdeaIndex);
	//SendIdea(ManagerRef->IdeaIndex);
}
//Called by CallMeeting
void UIdeaBacklogWidget::SendIdea(int Index) {

	//Gm populated in CallMeeting
	if (GM->MeetingDepartment == nullptr) {
		GEngine->AddOnScreenDebugMessage(102, 5.f, FColor::Red, "GM->MeetingDepartment is null");
	}
	else if (GM->MeetingDepartment != nullptr) {
		//auto tIdea = OfficeDepartment->IdeaList[Index];
		auto tIdea = GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->IdeaList[Index];
		if (tIdea != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(1036, 5.f, FColor::Red, "tIdea work");
			//GM->MeetingDepartment->TakeIdea(tIdea);
			GM->MeetingDepartmentList[GM->Character->CurrentFloor - 1]->TakeIdea(tIdea);
		}
		//GM->MeetingDepartment->TakeIdea(OfficeDepartment->IdeaList[ChosenIndex]);
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Meeting TakeIdea");
	}
}


void UIdeaBacklogWidget::SendIdeaFloorM(int Index) {

	//Gm populated in CallMeeting
	if (GM->MeetingDepartment == nullptr) {
		GEngine->AddOnScreenDebugMessage(102, 5.f, FColor::Red, "GM->MeetingDepartment is null");
	}
	else if (GM->MeetingDepartment != nullptr) {
		//auto tIdea = OfficeDepartment->IdeaList[Index];
		auto tIdea = GM->OfficeDepartmentList[0]->IdeaList[Index];
		if (tIdea != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(1036, 5.f, FColor::Red, "tIdea work");
			//GM->MeetingDepartment->TakeIdea(tIdea);
			GM->MeetingDepartmentList[GM->Character->CurrentFloor - 1]->TakeIdea(tIdea);
		}
		//GM->MeetingDepartment->TakeIdea(OfficeDepartment->IdeaList[ChosenIndex]);
		GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Red, "Meeting TakeIdea");
	}
}
