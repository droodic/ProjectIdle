// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemButton.h"
#include "Item.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Widgets/ShopWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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


	//ItemName_T->Text = FText::FromString(Item.GetDefaultObject()->ItemName);
	//ItemPrice_T->Text = FText::AsCurrency(Item.GetDefaultObject()->ItemPrice);

	//ItemID = Item.GetDefaultObject()->ItemID;

	if (!Item_Btn->OnClicked.IsBound())
	{
		Item_Btn->OnClicked.AddDynamic(this, &UItemButton::OnClicked);
	}
}

void UItemButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Item_Btn)
	{
		if (Item_Btn->HasUserFocus(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			Item_Btn->SetBackgroundColor(SelectedColor);
		}
		else
		{
			Item_Btn->SetBackgroundColor(FLinearColor::White);
		}
	}
}

void UItemButton::OnClicked()
{
	if (!InCheckout)
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Blue, "Item :" + Item->ItemName + " ID: " + FString::FromInt(ItemID));
		GameManager->ShopWidget->AddItemToCheckout(this->Item);
		GameManager->ShopWidget->CurrentItem = this->Item;
		//GameManager->ShopWidget->Buy();
	}
	else
	{
		GameManager->ShopWidget->RemoveItemFromCheckout(Item->ItemID);
	}
}