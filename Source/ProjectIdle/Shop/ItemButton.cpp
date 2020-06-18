// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemButton.h"
#include "Item.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Widgets/ShopWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UItemButton::UItemButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UItemButton::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = GetWorld()->GetGameInstance<UGameManager>();
	if (BPItem != nullptr) {
		Item = BPItem.GetDefaultObject();
		Item_I->SetBrushFromTexture(Item->ItemImage);
		ItemName_T->SetText(FText::FromString(Item->ItemName));
		ItemPrice_T->SetText(FText::AsCurrency(Item->ItemPrice));
		ItemID = Item->ItemID;
	}

	Item->ItemButton = this;


	if (!Item_Btn->OnClicked.IsBound())
	{
		Item_Btn->OnClicked.AddDynamic(this, &UItemButton::OnClicked);
	}
}

void UItemButton::OnClicked()
{
	if (!InCheckout)
	{
		GameManager->ShopWidget->AddItemToCheckout(this->Item);
		//GameManager->ShopWidget->CurrentItem = this->Item;
		//GameManager->ShopWidget->Buy();
	}
	else
	{
		GameManager->ShopWidget->RemoveItemFromCheckout(Item->ItemID);
	}
}
