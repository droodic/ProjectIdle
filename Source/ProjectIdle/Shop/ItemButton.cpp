// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemButton.h"
#include "Item.h"
#include "Engine.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemButton::NativeConstruct()
{
	Super::NativeConstruct();

	Item = BPItem.GetDefaultObject();

	Item_I->SetBrushFromTexture(Item->ItemImage);

	ItemName_T->SetText(FText::FromString(Item->ItemName));
	ItemPrice_T->SetText(FText::AsCurrency(Item->ItemPrice));

	ItemID = Item->ItemID;

	//ItemName_T->Text = FText::FromString(Item.GetDefaultObject()->ItemName);
	//ItemPrice_T->Text = FText::AsCurrency(Item.GetDefaultObject()->ItemPrice);

	//ItemID = Item.GetDefaultObject()->ItemID;

	if (!Item_Btn->OnClicked.IsBound())
	{
		Item_Btn->OnClicked.AddDynamic(this, &UItemButton::OnClicked);
	}
}

void UItemButton::OnClicked()
{
	GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Blue, "Item :" + Item->ItemName + " ID: " + FString::FromInt(ItemID));
}