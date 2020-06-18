// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryButton.h"
#include "ProjectIdle/Shop/Item.h"
#include "ProjectIdle/Workstation.h"
#include "ProjectIdle/GameManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UInventoryButton::UInventoryButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UInventoryButton::NativeConstruct() 
{
	Super::NativeConstruct();
	GameManager = GetWorld()->GetGameInstance<UGameManager>();

	if (!Item_Btn->OnClicked.IsBound())
	{
		Item_Btn->OnClicked.AddDynamic(this, &UInventoryButton::OnClicked);
	}
}

void UInventoryButton::OnClicked()
{
	CurrentStation->UpgradeMesh(0);
}