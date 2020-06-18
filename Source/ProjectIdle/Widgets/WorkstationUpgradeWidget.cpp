// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkstationUpgradeWidget.h"
#include "Engine.h"
#include "ProjectIdle/Shop/Item.h"
#include "ProjectIdle/Widgets/InventoryButton.h"
#include "ProjectIdle/GameManager.h"



void UWorkstationUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!Monitor_Btn->OnClicked.IsBound())
	{
		Monitor_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryMonitor);
	}

	if (!Desk_Btn->OnClicked.IsBound())
	{
		Desk_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::ShowInventoryDesk);
	}


	if (!Chair_Btn->OnClicked.IsBound())
	{

		//Chair_Btn->OnClicked.AddDynamic(this, &UWorkstationUpgradeWidget::Monitor);
	}


}


void UWorkstationUpgradeWidget::ShowInventory(ECategory ItemCategory) {

	//UItemButton* NewItemButton = CreateWidget<UItemButton>(this, ItemButtonWidgetClass);
	//NewItemButton->Item = Item;
	//NewItemButton->Item_I->SetBrushFromTexture(NewItemButton->Item->ItemImage);
	//NewItemButton->ItemName_T->SetText(FText::FromString(NewItemButton->Item->ItemName));
	//NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(NewItemButton->Item->ItemPrice));
	//InventoryScrollBox->AddChild(NewItemButton);

	InventoryScrollBox->ClearChildren();

	for (auto Item : GM->InventoryList) {
		//Show computercomponents 
		if (Item->ItemCategory == ItemCategory) {

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Computer Component :" + Item->ItemName);
			UInventoryButton* NewItemButton = CreateWidget<UInventoryButton>(this, InventoryButtonWidgetClass);
			NewItemButton->CurrentStation = Station;
			NewItemButton->Item = Item;
			NewItemButton->Item_I->SetBrushFromTexture(Item->ItemImage);
			NewItemButton->ItemName_T->SetText(FText::FromString(Item->ItemName));
			//NewItemButton->ItemPrice_T->SetText(FText::AsCurrency(Item->ItemPrice));
			InventoryScrollBox->AddChild(NewItemButton);
		}



	}




}


void UWorkstationUpgradeWidget::ShowInventoryMonitor() {
	ShowInventory(ECategory::ComputerComponents);
}

void UWorkstationUpgradeWidget::ShowInventoryDesk() {
	ShowInventory(ECategory::DeskAndChairs);
}

//void UWorkstationUpgradeWidget::Monitor()
//{
//	if (Station)
//	{
//		Station->UpgradeMesh(0);
//	}
//}
//
//
//
//void UWorkstationUpgradeWidget::Keyboard()
//{
//	if (Station)
//	{
//		Station->UpgradeMesh(1);
//	}
//}