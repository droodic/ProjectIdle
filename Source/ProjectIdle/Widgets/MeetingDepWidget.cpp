// Fill out your copyright notice in the Description page of Project Settings.



#include "MeetingDepWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "ProjectIdle/Widgets/MeetingDepWidget.h"
#include "ProjectIdle/GameHUD.h"


void UMeetingDepWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->MeetingWidget = this;

	if (!StartMeetingBtn->OnClicked.IsBound())
	{
		StartMeetingBtn->OnClicked.AddDynamic(this, &UMeetingDepWidget::StartMeeting);
	}

	//if (!Perfectionist_Btn->OnClicked.IsBound())
	//{
	//	Perfectionist_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::PerfectionistMode);
	//}

	//if (!CrunchTime_Btn->OnClicked.IsBound())
	//{
	//	CrunchTime_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::CrunchTimeMode);
	//}

	//if (!Default_Btn->OnClicked.IsBound())
	//{
	//	Default_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::DefaultMode);
	//}


}

void UMeetingDepWidget::StartMeeting()
{
	if (GM->IdeaInProduction) {
		if (SelectedApproach == "Default") {
			GM->SpeedRate = 1;
			GM->OfficeDepartment->AddedChance = 0.0f;
			GM->MeetingDepartment->BackFromMeeting();
		    //GM->MeetingDepartmentList[GM->OfficeDepartment->FloorLevel - 1]->BackFromMeeting();

			//T_SuccessChance->SetText(FText::AsPercent((GM->MeetingDepartment->CurrentIdea->SuccessChance / 100.f)));
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Default Approach"));
		}
		//GM->OfficeDepartment->AddedChance = 0;
		else if (SelectedApproach == "Perfectionist") {
			GM->SpeedRate = 0.75;
			GM->OfficeDepartment->AddedChance = 10.0f;
			GM->MeetingDepartment->BackFromMeeting();
			//GM->MeetingDepartmentList[GM->OfficeDepartment->FloorLevel - 1]->BackFromMeeting();


			//T_SuccessChance->SetText(FText::AsPercent((GM->MeetingDepartment->CurrentIdea->SuccessChance + 10.0f / 100.f)));
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Perfectionist approach"));
		}
		else if (SelectedApproach == "Crunch Time") {
			GM->SpeedRate = 1.25;
			GM->OfficeDepartment->AddedChance = -10.0f;
			GM->MeetingDepartment->BackFromMeeting();
			//GM->MeetingDepartmentList[GM->OfficeDepartment->FloorLevel - 1]->BackFromMeeting();
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Crunch time approach"));
		}
	}


	//StartMeetingBtn->SetIsEnabled(false);
}
