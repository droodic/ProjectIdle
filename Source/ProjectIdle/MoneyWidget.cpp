// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyWidget.h"

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