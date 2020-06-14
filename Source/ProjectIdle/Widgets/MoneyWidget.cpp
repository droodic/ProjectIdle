// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyWidget.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"

UMoneyWidget::UMoneyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMoneyWidget::UpdateMoney(int32 Value)
{
	TotalMoney->SetText(FText::FromString("Money: " + FString::FromInt(Value)));
}

void UMoneyWidget::ShowANotification(FString notifationText, float time)
{
	UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>();
	
	textBlock->Text = FText::FromString(notifationText);
	textBlock->SetAutoWrapText(true);
	NotificationVerticalBox->AddChildToVerticalBox(textBlock);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMoneyWidget::RemoveNotification, time, false);
}

void UMoneyWidget::RemoveNotification() 
{
	NotificationVerticalBox->RemoveChildAt(0);
}
