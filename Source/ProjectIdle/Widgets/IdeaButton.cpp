// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaButton.h"

UIdeaButton::UIdeaButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UIdeaButton::NativeConstruct() 
{

}

/*
UIdeaButton* UIdeaButton::IdeaButtonConstructor(FLinearColor coverColor, FString gameTitle, FString gameDescription, FText genre, float successChance, FString mainWeight)
{
    UIdeaButton* ideaButton;

    ideaButton->GameCover_I->SetColorAndOpacity(coverColor);
    
    ideaButton->GameTitle_T->SetText(FText::FromString(gameTitle));
    ideaButton->GameDescription_T->SetText(FText::FromString(gameDescription));
    ideaButton->Genre_T->SetText(genre);
    ideaButton->SuccessChance_T->SetText(FText::AsPercent(successChance / 100.f));
    ideaButton->Weight_T->SetText(FText::FromString(mainWeight));

    return ideaButton;
}

UIdeaButton* UIdeaButton::IdeaButtonConstructor(Idea* idea)
{
    UIdeaButton* ideaButton;

    ideaButton->GameCover_I->SetColorAndOpacity(idea->CoverColor);
    
    ideaButton->GameTitle_T->SetText(FText::FromString(idea->IdeaName));
    ideaButton->GameDescription_T->SetText(FText::FromString(idea->IdeaDescription));
    ideaButton->Genre_T->SetText(Idea::GenreToText(idea->Genre));
    ideaButton->SuccessChance_T->SetText(FText::AsPercent(idea->SuccessChance / 100.f));
    ideaButton->Weight_T->SetText(FText::FromString(idea->MainWeight));

    return ideaButton;
}
*/
