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
	if (ItemButtons.Num() > 0)
	{
		for (size_t i = 0; i < ItemButtons.Num(); i++)
		{
			ItemButtons[i]->Item->ItemName;
			GameManager->Money -= ItemButtons[i]->Item->ItemPrice;

			CheckoutItems_WB->RemoveChild(ItemButtons[i]);
			ItemButtons.Remove(ItemButtons[i]);
		}
	}
}

void UShopWidget::AddItemToCheckout(class AItem* itemButton)
{
	GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Green, "Add Item Checkout called");
	GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Blue, "Item :" + itemButton->ItemName + " ID: " + FString::FromInt(itemButton->ItemPrice));

	if (ItemButtons.Num() != 0)
	{
		for (size_t i = 0; i < ItemButtons.Num(); i++)
		{
			if (ItemButtons[i]->ItemID != itemButton->ItemID)
			{
				if (ItemButtonClass != nullptr)
				{
					auto NewItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

					NewItemButton->Item = itemButton;

					NewItemButton->Item_I->SetBrushFromTexture(NewItemButton->Item->ItemImage);

					NewItemButton->ItemName_T->SetText(FText::FromString(NewItemButton->Item->ItemName));
					NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(NewItemButton->Item->ItemPrice));

					NewItemButton->InCheckout = true;

					ItemButtons.Add(NewItemButton);
					CheckoutItems_WB->AddChildToWrapBox(NewItemButton);

					CheckoutCount++;
					CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

					Total += NewItemButton->Item->ItemPrice;
					TotalMoney_T->SetText(FText::AsCurrency(Total));

					GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Green, "Item :" + NewItemButton->Item->ItemName + " ID: " + FString::FromInt(NewItemButton->Item->ItemPrice));
				}
			}
			else
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Visible);
				ItemButtons[i]->ItemCount++;
				ItemButtons[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(ItemButtons[i]->ItemCount)));

				Total += ItemButtons[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));
			}
		}
	}
	else
	{
		if (ItemButtonClass != nullptr)
		{
			auto NewItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

			NewItemButton->Item = itemButton;

			NewItemButton->Item_I->SetBrushFromTexture(NewItemButton->Item->ItemImage);

			NewItemButton->ItemName_T->SetText(FText::FromString(NewItemButton->Item->ItemName));
			NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(NewItemButton->Item->ItemPrice));

			NewItemButton->InCheckout = true;

			ItemButtons.Add(NewItemButton);
			CheckoutItems_WB->AddChildToWrapBox(NewItemButton);

			CheckoutCount++;
			CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

			Total += NewItemButton->Item->ItemPrice;
			TotalMoney_T->SetText(FText::AsCurrency(Total));

			GEngine->AddOnScreenDebugMessage(103, 5.f, FColor::Green, "Item :" + NewItemButton->Item->ItemName + " ID: " + FString::FromInt(NewItemButton->Item->ItemPrice));
		}
	}
}

void UShopWidget::RemoveItemFromCheckout(int itemID)
{
	for (size_t i = 0; i < ItemButtons.Num(); i++)
	{
		if (ItemButtons[i]->ItemID == itemID)
		{
			if (ItemButtons[i]->ItemCount == 1)
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Visible);
				ItemButtons[i]->ItemCount = 1;
				ItemButtons[i]->ItemCount_T->SetText(FText::FromString(" "));

				CheckoutItems_WB->RemoveChild(ItemButtons[i]);
				ItemButtons.RemoveAt(i);

				CheckoutCount--;
				CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

				Total -= ItemButtons[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "Item Removed");
			}
			else if (ItemButtons[i]->ItemCount > 1)
			{
				//ItemButtons[i]->ItemCount_T->SetVisibility(ESlateVisibility::Hidden);
				ItemButtons[i]->ItemCount--;
				ItemButtons[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(ItemButtons[i]->ItemCount)));

				Total -= ItemButtons[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));
			}
		}
	}
}

void UShopWidget::Return()
{
	OfficeDepartment->ShopReturn();
}

