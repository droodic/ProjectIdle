// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaButton.h"
#include "Engine.h"
#include "IdeaBacklogWidget.h"
#include "Components/Button.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/CeoDepMenuWidget.h"

UIdeaButton::UIdeaButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UIdeaButton::NativeConstruct() 
{
    Super::NativeConstruct(); 

    if (!IdeaButton->OnClicked.IsBound())
    {
        IdeaButton->OnClicked.AddDynamic(this, &UIdeaButton::ButtonClicked);
    }
}

void UIdeaButton::ButtonClicked()
{
    if (IsFinished && !IsPublished)
    {
        OfficeDepartment->OfficeDepMenuWidget->PublishGame_Btn->SetIsEnabled(true);
        OfficeDepartment->OfficeDepMenuWidget->ChosenIndex = storedIndex;
    }
    else if (IsPublished) 
    {
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "The game is published");
    }
    else /*if (!IsInProduction)*/
    {
        BacklogWidget->ChosenIndex = storedIndex;
        BacklogWidget->CallMeetingBtn->SetIsEnabled(true);
    }
}

void UIdeaButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    if (IdeaButton)
    {
        if (IdeaButton->HasUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
        {
            IdeaButton->SetBackgroundColor(SelectedColor);
        }
        else
        {
            IdeaButton->SetBackgroundColor(FLinearColor::White);
        }
    }
}


