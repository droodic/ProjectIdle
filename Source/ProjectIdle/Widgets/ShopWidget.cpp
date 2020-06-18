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
	if (CheckList.Num() > 0)
	{
		if (GameManager->Money > Total)
		{
			for (size_t i = 0; i < CheckList.Num(); i++)
			{
				//GameManager->InventoryList.Add(ItemButtons[i]);
			}

			GameManager->Money -= Total;

			CheckoutItems_WB->ClearChildren();
			CheckList.Empty();

			Total = 0;
			CheckoutCount = 0;

			TotalMoney_T->SetText(FText::AsCurrency(Total));
			CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));

			Money_T->SetText(FText::AsCurrency(GameManager->Money));
		}
		else
		{
			NotEnoughMoney_T->SetText(FText::FromString("Not enough money."));

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UShopWidget::RemoveNotEnoughMoney, 5.f, false);
		}
	}
}

void UShopWidget::AddItemToCheckout(class AItem* item)
{
	bool isInCheckout = false;

	if (CheckList.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "List is not empty");

		for (size_t i = 0; i < CheckList.Num(); i++)
		{
			if (CheckList[i]->ItemID == item->ItemID)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Is in checkout");

				CheckList[i]->ItemCount++;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckList[i]->ItemCount)));

				Total += CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));
				
				isInCheckout = true;

				break;
			}
		}

		if (!isInCheckout)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Is not in Checkout");

			auto ItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

			ItemButton->Item = item;
			ItemButton->BPItem = item->ItemButton->BPItem;

			ItemButton->ItemID = item->ItemID;

			ItemButton->InCheckout = true;

			Total += ItemButton->Item->ItemPrice;
			TotalMoney_T->SetText(FText::AsCurrency(Total));

			CheckList.Add(ItemButton);
			CheckoutItems_WB->AddChildToWrapBox(ItemButton);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "List is empty");

		auto ItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

		ItemButton->BPItem = item->ItemButton->BPItem;
		ItemButton->Item = item;

		ItemButton->ItemID = item->ItemID;

		ItemButton->InCheckout = true;

		Total += ItemButton->Item->ItemPrice;
		TotalMoney_T->SetText(FText::AsCurrency(Total));

		CheckList.Add(ItemButton);
		CheckoutItems_WB->AddChildToWrapBox(ItemButton);
	}

	CheckoutCount++;
	CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
}

void UShopWidget::RemoveItemFromCheckout(int itemID)
{
	for (size_t i = 0; i < CheckList.Num(); i++)
	{
		if (CheckList[i]->ItemID == itemID)
		{
			if (CheckList[i]->ItemCount == 1)
			{
				CheckList[i]->ItemCount = 1;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(" "));

				Total -= CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				CheckoutItems_WB->RemoveChild(CheckList[i]);
				CheckList.RemoveAt(i);

				GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::Red, "Item Removed");

				break;
			}
			else if (CheckList[i]->ItemCount > 1)
			{
				CheckList[i]->ItemCount--;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckList[i]->ItemCount)));

				Total -= CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				break;
			}
		}
	}

	CheckoutCount--;
	CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
}

void UShopWidget::RemoveNotEnoughMoney()
{
	NotEnoughMoney_T->SetText(FText::FromString(""));
}

void UShopWidget::Return()
{
	OfficeDepartment->ShopReturn();
}
