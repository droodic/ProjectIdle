// Fill out your copyright notice in the Description page of Project Settings.


#include "IdeaBacklogWidget.h"
#include "Engine.h"
#include "Components\Button.h"

void UIdeaBacklogWidget::DisplayNewIdea() {
	GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Red, "Displaying new idea");
	if (!IdeaButton1->IsVisible()) {
		IdeaButton1->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!IdeaButton2->IsVisible()) {
		IdeaButton2->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		IdeaButton3->SetVisibility(ESlateVisibility::Visible);
	}
}

void UIdeaBacklogWidget::NativeConstruct() {
	Super::NativeConstruct();
	//IdeaButton1->SetVisibility(ESlateVisibility::Hidden);
	//IdeaButton2->SetVisibility(ESlateVisibility::Hidden);
	//IdeaButton3->SetVisibility(ESlateVisibility::Hidden); //array?
}