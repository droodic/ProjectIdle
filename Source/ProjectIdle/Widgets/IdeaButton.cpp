// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaButton.h"
#include "Engine.h"
#include "IdeaBacklogWidget.h"
#include "Components/Button.h"

UIdeaButton::UIdeaButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UIdeaButton::NativeConstruct() 
{
    Super::NativeConstruct(); 

    if (IdeaButton->OnClicked.IsBound())
    {
        IdeaButton->OnClicked.AddDynamic(this, &UIdeaButton::CallIdeaButton);
    }
}

void UIdeaButton::CallIdeaButton()
{
    GEngine->AddOnScreenDebugMessage(6, 5.f, FColor::Green, "Call Idea button");

    BacklogWidget->ChosenIndex = storedIndex;
    BacklogWidget->CallMeetingBtn->SetIsEnabled(true);
    IdeaButton->ColorAndOpacity = FLinearColor::MakeRandomColor();
}
