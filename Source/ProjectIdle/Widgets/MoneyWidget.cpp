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
	TotalMoney->SetText(FText::FromString("$" + FString::FromInt(Value) + ".00"));
}

void UMoneyWidget::ShowANotification(FString notifationText, FLinearColor color, float time)
{
	UBorder* border = WidgetTree->ConstructWidget<UBorder>();
	UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>();
	
	textBlock->Text = FText::FromString(notifationText);
	textBlock->SetAutoWrapText(true);
	border->AddChild(textBlock);
	border->SetContentColorAndOpacity(color);
	border->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.3f));

	NotificationVerticalBox->AddChildToVerticalBox(border);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMoneyWidget::RemoveNotification, time, false);
}

void UMoneyWidget::RemoveNotification() 
{
	NotificationVerticalBox->RemoveChildAt(0);
}
