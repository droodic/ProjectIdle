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

void UItemButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (BPItem != nullptr)
	{
		Item = BPItem.GetDefaultObject();
		Item->ItemButton = this;
		ItemID = Item->ItemID;

		Item_I->SetBrushFromTexture(Item->ItemImage);
		ItemName_T->SetText(FText::FromString(Item->ItemName));
		ItemPrice_T->SetText(FText::AsCurrency(Item->ItemPrice));
	}
}

void UItemButton::NativeConstruct()
{
	GameManager = GetWorld()->GetGameInstance<UGameManager>();

	Super::NativeConstruct();

	if (!Item_Btn->OnClicked.IsBound())
	{
		Item_Btn->OnClicked.AddDynamic(this, &UItemButton::OnClicked);
	}

	BoughtItem_I->SetColorAndOpacity(FLinearColor(.3f, .3f, .3f, .5f));
}

void UItemButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!IsDescriptionOn)
	{
		if (IsHovered())
		{
			if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::D))
			{
				IsDescriptionOn = true;

				GameManager->ShopWidget->DescriptionPanel->SetVisibility(ESlateVisibility::Visible);
				GameManager->ShopWidget->Description_T->SetText(FText::FromString(Item->ItemDescription));

				if (Item->ItemCompileRate > 0)
				{
					GameManager->ShopWidget->DescriptionStats_T->SetText(FText::FromString("Compile time descrease: " + FString::FromInt(Item->ItemCompileRate) + "%"));
				}
				else
				{
					GameManager->ShopWidget->DescriptionStats_T->SetText(FText::FromString(""));
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(101, 5.f, FColor::White, (IsDescriptionOn) ? "True" : "False ");
}

void UItemButton::OnClicked()
{
	if (!InCheckout)
	{
		GameManager->ShopWidget->AddItemToCheckout(this->Item);

		if (Item->ItemCategory == ECategory::Materials)
		{
			this->BoughtItem_I->SetVisibility(ESlateVisibility::Visible);
			this->Bought_T->SetVisibility(ESlateVisibility::Visible);
			this->Bought_T->SetText(FText::FromString("In Checkout"));
		}
	}
	else
	{
		GameManager->ShopWidget->RemoveItemFromCheckout(Item->ItemID);

		if (Item->ItemCategory == ECategory::Materials)
		{
			for (size_t i = 0; i < GameManager->ShopWidget->Tab4->GetChildrenCount(); i++)
			{
				auto materialButton = Cast<UItemButton>(GameManager->ShopWidget->Tab4->GetChildAt(i));

				if (Item->ItemID == materialButton->ItemID)
				{
					materialButton->BoughtItem_I->SetVisibility(ESlateVisibility::Hidden);
					materialButton->Bought_T->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}