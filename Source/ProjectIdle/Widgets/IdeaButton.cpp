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

    if (!IdeaButton->OnClicked.IsBound())
    {
        IdeaButton->OnClicked.AddDynamic(this, &UIdeaButton::ButtonClicked);
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

void UIdeaButton::ButtonClicked()
{
    BacklogWidget->ChosenIndex = storedIndex;
    BacklogWidget->CallMeetingBtn->SetIsEnabled(true);
}
