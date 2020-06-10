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
	//Notifications_T->SetColorAndOpacity(color);
	NotificationText = FText::FromString(notifationText);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMoneyWidget::RemoveNotification, time, false);
}

void UMoneyWidget::RemoveNotification() 
{
	NotificationText = FText::FromString(" ");
}
