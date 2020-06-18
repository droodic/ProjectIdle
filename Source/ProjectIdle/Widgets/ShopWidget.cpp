// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/Shop/ItemButton.h"
#include "ProjectIdle/Shop/Item.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = GetWorld()->GetGameInstance<UGameManager>();
	GameManager->ShopWidget = this;

	Money_T->SetText(FText::AsCurrency(GameManager->Money));

	if (!Buy_Btn->OnClicked.IsBound())
	{
		Buy_Btn->OnClicked.AddDynamic(this, &UShopWidget::Buy);
	}
	if (!ShopReturn_Btn->OnClicked.IsBound())
	{
		ShopReturn_Btn->OnClicked.AddDynamic(this, &UShopWidget::Return);
	}
}

void UShopWidget::Buy()
{
	auto TotalCost = 0;

	//Calculate TotalCost, nvm saw theres total already
	//for (auto ItemButton : CheckoutItemBtnList) {
	//	TotalCost += ItemButton->Item->ItemPrice;
	//}

	if (GameManager->Money >= Total) {
		for (auto ItemButton : CheckoutItemBtnList) {
			GameManager->InventoryList.Add(ItemButton->Item);
			GameManager->Money -= ItemButton->Item->ItemPrice; //Is this equal to Total? If not, remove from GM->Money the total outside of for, or fix Total
			CheckoutItems_WB->RemoveChild(ItemButton);
		}

		CheckoutCount = 0;
		Money_T->SetText(FText::AsCurrency(GameManager->Money-=Total));
		Total = 0;
		TotalMoney_T->SetText(FText::AsCurrency(0));
		CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
		CheckoutItemBtnList.Empty();
	}
}

void UShopWidget::AddItemToCheckout(class AItem* Item)
{
	GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Green, "Add Item Checkout called");
	GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Blue, "Item :" + Item->ItemName + " ID: " + FString::FromInt(Item->ItemPrice));

	if (CheckoutItemBtnList.Num() != 0)
	{
		for (int i = 0; i < CheckoutItemBtnList.Num(); i++)
		{
			if (CheckoutItemBtnList[i]->ItemID != Item->ItemID)
			{
				if (ItemButtonClass != nullptr)
				{
					auto NewItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);
					

					//NewItemButton->BPItem = itemButton->GetDefaultObject();
					NewItemButton->Item = Item;
					NewItemButton->Item_I->SetBrushFromTexture(NewItemButton->Item->ItemImage);

					NewItemButton->ItemName_T->SetText(FText::FromString(NewItemButton->Item->ItemName));
					NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(NewItemButton->Item->ItemPrice));

					NewItemButton->InCheckout = true;

					CheckoutItemBtnList.Add(NewItemButton);
					CheckoutItems_WB->AddChildToWrapBox(NewItemButton);

					CheckoutCount++;
					CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

					Total += NewItemButton->Item->ItemPrice;
					TotalMoney_T->SetText(FText::AsCurrency(Total));

					GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Green, "Item :" + NewItemButton->Item->ItemName + " ID: " + FString::FromInt(NewItemButton->Item->ItemPrice));
					break;
				}
			}
			else
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Visible);
				CheckoutItemBtnList[i]->ItemCount++;
				CheckoutItemBtnList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckoutItemBtnList[i]->ItemCount)));

				Total += CheckoutItemBtnList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));
			}
		}
	}
	else
	{
		if (ItemButtonClass != nullptr)
		{
			UItemButton* NewItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

			NewItemButton->Item = Item;
			NewItemButton->Item_I->SetBrushFromTexture(NewItemButton->Item->ItemImage);
			NewItemButton->ItemName_T->SetText(FText::FromString(NewItemButton->Item->ItemName));
			NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(NewItemButton->Item->ItemPrice));
			NewItemButton->InCheckout = true;

			CheckoutItemBtnList.Add(NewItemButton);
			CheckoutItems_WB->AddChildToWrapBox(NewItemButton);
			CheckoutCount++;
			CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

			Total += NewItemButton->Item->ItemPrice;
			TotalMoney_T->SetText(FText::AsCurrency(Total));

		}
	}
}

void UShopWidget::RemoveItemFromCheckout(int itemID)
{
	for (int i = 0; i < CheckoutItemBtnList.Num(); i++)
	{
		if (CheckoutItemBtnList[i]->ItemID == itemID)
		{
			if (CheckoutItemBtnList[i]->ItemCount == 1)
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Visible);
				CheckoutItemBtnList[i]->ItemCount = 1;
				CheckoutItemBtnList[i]->ItemCount_T->SetText(FText::FromString(" "));

				CheckoutItems_WB->RemoveChild(CheckoutItemBtnList[i]);
				CheckoutItemBtnList.RemoveAt(i);

				CheckoutCount--;
				CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

				Total -= CheckoutItemBtnList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "Item Removed");
			}
			else if (CheckoutItemBtnList[i]->ItemCount > 1)
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Hidden);
				CheckoutItemBtnList[i]->ItemCount--;
				CheckoutItemBtnList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckoutItemBtnList[i]->ItemCount)));

				Total -= CheckoutItemBtnList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));
			}
		}
	}
}

void UShopWidget::Return()
{
	OfficeDepartment->ShopReturn();
}

