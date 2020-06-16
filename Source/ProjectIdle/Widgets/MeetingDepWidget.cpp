// Fill out your copyright notice in the Description page of Project Settings.



#include "MeetingDepWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/Widgets/MeetingDepWidget.h"
#include "ProjectIdle/GameHUD.h"


void UMeetingDepWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->MeetingWidget = this;

	if (!Perfectionist_Btn->OnClicked.IsBound())
	{
		Perfectionist_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::PerfectionistMode);
	}

	if (!CrunchTime_Btn->OnClicked.IsBound())
	{
		CrunchTime_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::CrunchTimeMode);
	}

	if (!Default_Btn->OnClicked.IsBound())
	{
		Default_Btn->OnClicked.AddDynamic(this, &UMeetingDepWidget::DefaultMode);
	}


}

void UMeetingDepWidget::PerfectionistMode()
{
	//GM->OfficeDepartment->AddedChance = 0;
	GM->SpeedRate = 0.25;
	GM->OfficeDepartment->AddedChance = 10.0f;
	GM->MeetingDepartment->BackFromMeeting();

}

void UMeetingDepWidget::CrunchTimeMode()
{
	//GM->OfficeDepartment->AddedChance = 0;
	GM->SpeedRate = 1.25;
	GM->OfficeDepartment->AddedChance = -10.0f;
	GM->MeetingDepartment->BackFromMeeting();
}

void UMeetingDepWidget::DefaultMode()
{
	GM->SpeedRate = 1;
	GM->OfficeDepartment->AddedChance = 0;
	GM->MeetingDepartment->BackFromMeeting();
}