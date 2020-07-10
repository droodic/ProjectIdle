// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkstationUpgradeWidget.h"
#include "Engine.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Shop/Item.h"
#include "ProjectIdle/Shop/ItemButton.h"
#include "ProjectIdle/Widgets/InventoryButton.h"

void UWorkstationUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!Monitor_Btn->OnClicked.IsBound())
	{
		Monitor_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryMonitor);
	}
	if (!Keyboard_Btn->OnClicked.IsBound())
	{
		Keyboard_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryKeyboard);
	}
	if (!Desk_Btn->OnClicked.IsBound())
	{
		Desk_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryDesk);
	}
	if (!Chair_Btn->OnClicked.IsBound())
	{
		Chair_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryChair);
	}
	if (!ReturnUpgrBtn->OnClicked.IsBound())
	{
		ReturnUpgrBtn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::CloseUpgrWidget);
	}
}

void UWorkstationUpgradeWidget::ShowInventory(ESubCategory ItemCategory) 
{
	InventoryWrapBox->ClearChildren();

	TArray<AItem*> inventoryList; 
	GM->InventoryList.GenerateKeyArray(inventoryList);

	for (auto Item : inventoryList) 
	{
		//Show computercomponents 
		if (Item->ItemSubCategory == ItemCategory) 
		{
			UInventoryButton* NewItemButton = CreateWidget<UInventoryButton>(this, InventoryButtonWidgetClass);
			NewItemButton->CurrentStation = Station;
			NewItemButton->Item = Item;
			NewItemButton->Item_I->SetBrushFromTexture(Item->ItemImage);
			NewItemButton->ItemName_T->SetText(FText::FromString(Item->ItemName));

			auto itemCount = GM->InventoryList.FindRef(Item);

			if (itemCount > 1)
			{
				NewItemButton->ItemCount_T->SetText(FText::FromString(FString::FromInt(itemCount)));
			}

			InventoryWrapBox->AddChild(NewItemButton);
		}
	}
}

void UWorkstationUpgradeWidget::ShowInventoryMonitor() 
{
	ShowInventory(ESubCategory::Monitor);
}

void UWorkstationUpgradeWidget::ShowInventoryDesk() 
{
	ShowInventory(ESubCategory::Desk);
}

void UWorkstationUpgradeWidget::ShowInventoryChair() 
{
	ShowInventory(ESubCategory::Chair);
}

void UWorkstationUpgradeWidget::ShowInventoryKeyboard() 
{
	ShowInventory(ESubCategory::Keyboard);
}

void UWorkstationUpgradeWidget::CloseUpgrWidget()
{
	RemoveFromViewport();
	GM->IsWidgetInDisplay = false;
}
