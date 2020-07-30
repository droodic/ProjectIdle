// Fill out your copyright notice in the Description page of Project Settings.


#include "CeoDepMenuWidget.h"
#include "Engine.h"
#include "Idea.h"
#include "GameManager.h"
#include "OfficeDepartment.h"
#include "Workstation.h"
#include "Shop/Item.h"
#include "Shop/ItemButton.h"
#include "Blueprint/UserWidget.h"
#include "WorldObject/Wall.h"
#include "WorldObject/Elevator.h"
#include "Widgets/IdeaButton.h"
#include "Widgets/InventoryButton.h"
#include "Workstations/ArtistStation.h"
#include "Workstations/ProgrammerStation.h"
#include "Components/Button.h"
#include "ProjectIdle/Workstations/SupervisorWorkstation.h"
#include "WorldObject/Wall.h"

void UCeoDepMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//AddToRoot();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	if (!Hire_Prog_Btn->OnClicked.IsBound())
	{
		Hire_Prog_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallProgrammerSpawn);
	}
	if (!Hire_Artist_Btn->OnClicked.IsBound())
	{
		Hire_Artist_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallArtistSpawn);
	}
	if (!Hire_ProgSup_Btn->OnClicked.IsBound())
	{
		Hire_ProgSup_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallProgrammerSupSpawn);
	}
	if (!Hire_ArtistSup_Btn->OnClicked.IsBound())
	{
		Hire_ArtistSup_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallArtistSupSpawn);
	}
	if (!Hire_FloorManager_Btn->OnClicked.IsBound())
	{
		Hire_FloorManager_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CallFloorManagerSpawn);
	}
	if (!PublishGame_Btn->OnClicked.IsBound())
	{
		PublishGame_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::PublishGame);
	}
	if (!CreateDep_Btn->OnClicked.IsBound())
	{
		CreateDep_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::CreateDepartment);
	}
	if (!EditPlacedItems_Btn->OnClicked.IsBound())
	{
		EditPlacedItems_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::EditPlacedItems);
	}
	if (!Return_Btn->OnClicked.IsBound())
	{
		Return_Btn->OnClicked.AddDynamic(this, &UCeoDepMenuWidget::Return);
	}
}

void UCeoDepMenuWidget::CallProgrammerSpawn()
{
	int32 length = GM->WorkstationList.Num();
	int32 numberOfProgrammerStation = 0;
	int32 numberOfArtistStation = 0;

	for (int i = 0; i < length; i++)
	{
		if (GM->WorkstationList[i]->StationRole == ERole::Programmer)
		{
			numberOfProgrammerStation++;
		}
		if (GM->WorkstationList[i]->StationOwnerPosition == EPosition::Supervisor && GM->WorkstationList[i]->StationRole == ERole::Programmer)
		{
			numberOfProgrammerStation--;
		}
	}

	if (numberOfProgrammerStation > GM->NumOfProgrammers && GM->FloorList[GM->Character->CurrentFloor - 1]->FloorProgrammerCount < 3)
	{
		if (GM->Money >= 10000) //make money editable inspector constant that scales up , same for all dep & sup hire
		{
			GM->Money -= 10000;
			ActivateWorkstation(ERole::Programmer, EPosition::Intern, false);
			OfficeDepartment->GenerateActor(0, ERole::Programmer);
		}
	}
}

void UCeoDepMenuWidget::CallProgrammerSupSpawn()
{
	//if (!GM->ProgrammingDepartment->HasSupervisor && GM->Money >= 30000) {
	if (!GM->FloorList[GM->Character->CurrentFloor - 1]->ProgrammerSupOnCurrentFloor && GM->Money >= 30000) {
		GM->Money -= 30000;
		GM->ProgrammingDepartment->HasSupervisor = true;
		GM->FloorList[GM->Character->CurrentFloor - 1]->ProgrammerSupOnCurrentFloor = true;
		GM->FloorList[GM->Character->CurrentFloor - 1]->SupOnCurrentFloor = true;
		ActivateWorkstation(ERole::Programmer, EPosition::Supervisor, true);
		OfficeDepartment->GenerateActor(2, ERole::Programmer);
		GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->OfficeDepMenuWidget->Hire_ProgSup_Btn->SetIsEnabled(false);
		//Hire_ProgSup_Btn->SetIsEnabled(false);
		//OfficeDepartment->GetDepartmentUIValues();
	}
}

void UCeoDepMenuWidget::CallArtistSupSpawn()
{
	//if (!GM->ArtistDepartment->HasSupervisor && GM->Money >= 30000) {
	  if (!GM->FloorList[GM->Character->CurrentFloor - 1]->ArtistSupOnCurrentFloor && GM->Money >= 30000) {
		GM->Money -= 30000;
		ActivateWorkstation(ERole::Artist, EPosition::Supervisor, true);
		GM->FloorList[GM->Character->CurrentFloor - 1]->ArtistSupOnCurrentFloor = true;
		GM->FloorList[GM->Character->CurrentFloor - 1]->SupOnCurrentFloor = true;

		GM->ArtistDepartment->HasSupervisor = true;
		OfficeDepartment->GenerateActor(2, ERole::Artist);
		GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->OfficeDepMenuWidget->Hire_ArtistSup_Btn->SetIsEnabled(false);
		//Hire_ArtistSup_Btn->SetIsEnabled(false);
		//OfficeDepartment->GetDepartmentUIValues();
	}
}

void UCeoDepMenuWidget::CallFloorManagerSpawn()
{
	//if (OfficeDepartment->ManagerRef == nullptr && GM->Money >= 100000) {
	  if(GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->ManagerRef == nullptr && GM->Money >= 100000) {
		GM->Money -= 100000;
		//ActivateWorkstation(ERole::Artist, EPosition::FloorManager, true);
		//GM->ArtistDepartment->HasSupervisor = true;
		OfficeDepartment->GenerateActor(5, ERole::Management);
		for (auto Office : GM->OfficeDepartmentList)
		{
			Office->OfficeDepMenuWidget->Hire_FloorManager_Btn->SetIsEnabled(false);
		}

		for (auto OfficeOffline : GM->UnassignedOfficeDepartmentList)
		{
			OfficeOffline->OfficeDepMenuWidget->Hire_FloorManager_Btn->SetIsEnabled(false);
		}
		//Hire_FloorManager_Btn->SetIsEnabled(false);
		//OfficeDepartment->GetDepartmentUIValues();
	}
}

void UCeoDepMenuWidget::CallArtistSpawn()
{
	int32 length = GM->WorkstationList.Num();
	int32 numberOfProgrammerStation = 0;
	int32 numberOfArtistStation = 0;

	for (int i = 0; i < length; i++)
	{
		if (GM->WorkstationList[i]->StationRole == ERole::Artist)
		{
			numberOfArtistStation++;
		}
		if (GM->WorkstationList[i]->StationOwnerPosition == EPosition::Supervisor && GM->WorkstationList[i]->StationRole == ERole::Artist)
		{
			numberOfArtistStation--;
		}
	}
	if (numberOfArtistStation > GM->NumOfArtists && GM->FloorList[GM->Character->CurrentFloor - 1]->FloorArtistCount < 3)
	{
		if (GM->Money >= 10000)
		{
			GM->Money -= 10000;
			ActivateWorkstation(ERole::Artist, EPosition::Intern, false);
			OfficeDepartment->GenerateActor(1, ERole::Artist);
		}
	}
}

//Delegate
void UCeoDepMenuWidget::CallHiring()
{
	OfficeDepartment->GenerateActor(3, ERole::Artist);
}

void UCeoDepMenuWidget::ActivateWorkstation(ERole StationRole, EPosition OwnerPosition, bool IsSupervisor)
{
	int Length = GM->WorkstationList.Num();

	if (!IsSupervisor)
	{
		for (int i = 0; i < Length; i++)
		{
			if (!GM->WorkstationList[i]->IsEnabled && GM->WorkstationList[i]->StationRole == StationRole && !Cast<ASupervisorWorkstation>(GM->WorkstationList[i]))
			{
				if (GM->WorkstationList[i]->FloorLevel == GM->Character->CurrentFloor)
				{
					GM->WorkstationList[i]->EnableStation(true);
					return;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < Length; i++)
		{
			if (!GM->WorkstationList[i]->IsEnabled && GM->WorkstationList[i]->StationRole == StationRole && GM->WorkstationList[i]->StationOwnerPosition == OwnerPosition)
			{
				if (GM->WorkstationList[i]->FloorLevel == GM->Character->CurrentFloor)
				{
					GM->WorkstationList[i]->EnableStation(true);
					return;
				}
			}
		}
	}
}

void UCeoDepMenuWidget::GetFinishedIdea(Idea* idea)
{
	idea->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	OfficeDepartment->FinishedIdeaList.Insert(idea, Index);
	AddValuesToButton(OfficeDepartment->FinishedIdeaList[Index]);

	IdeaScrollBox->AddChild(OfficeDepartment->FinishedIdeaList[Index]->IdeaButton);

	Index++;
}

void UCeoDepMenuWidget::ClearFinishedGames()
{
	//->IdeaButton = Cast<UIdeaButton>(CreateWidget(this, IdeaButtonWidgetClass));
	if (OfficeDepartment->FinishedIdeaList.Num() > 0) {
		OfficeDepartment->FinishedIdeaList.Empty();
	}
	if (IdeaScrollBox->GetChildrenCount() > 0) {
		IdeaScrollBox->ClearChildren();
		Index = 0;
	}
}

void UCeoDepMenuWidget::AddItemToInventory(AItem* item)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Once from function");

	UInventoryButton* newItemButton = CreateWidget<UInventoryButton>(this, InventoryButtonWidgetClass);

	newItemButton->Item = item;
	newItemButton->Item->ItemBP = item->ItemBP;
	newItemButton->Item_I->SetBrushFromTexture(item->ItemImage);
	newItemButton->ItemName_T->SetText(FText::FromString(item->ItemName));

	if (item->ItemSubCategory == ESubCategory::Other)
	{
		TMap<AItem*, int> itemsInInventory;

		if (OfficeDecoration_WB->GetChildrenCount() > 0)
		{
			for (auto items : OfficeDecoration_WB->GetAllChildren())
			{
				auto itemInButton = Cast<UInventoryButton>(items);
				itemsInInventory.Add(itemInButton->Item, itemInButton->Item->ItemCount);
			}
		}
		else
		{
			newItemButton->Item->ItemCount = item->ItemButton->ItemCount;

			if (newItemButton->Item->ItemCount > 1)
			{
				newItemButton->ItemCount_T->SetText(FText::FromString(FString::FromInt(newItemButton->Item->ItemCount)));
			}

			OfficeDecoration_WB->AddChildToWrapBox(newItemButton);

			return;
		}

		if (itemsInInventory.Contains(item))
		{
			for (int i = 0; i < OfficeDecoration_WB->GetChildrenCount(); i++)
			{
				auto button = Cast<UInventoryButton>(OfficeDecoration_WB->GetChildAt(i));

				if (item->ItemID == button->Item->ItemID)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Once from loop, found id");

					button->Item->ItemCount += item->ItemButton->ItemCount;
					button->ItemCount_T->SetText(FText::FromString(FString::FromInt(button->Item->ItemCount)));
				}
			}
		}
		else
		{
			newItemButton->Item->ItemCount = item->ItemButton->ItemCount;

			if (newItemButton->Item->ItemCount > 1)
			{
				newItemButton->ItemCount_T->SetText(FText::FromString(FString::FromInt(newItemButton->Item->ItemCount)));
			}

			OfficeDecoration_WB->AddChildToWrapBox(newItemButton);
		}
	}
	else if (item->ItemSubCategory == ESubCategory::Floor)
	{
		FloorMaterial_HB->AddChildToHorizontalBox(newItemButton);
	}
	else if (item->ItemSubCategory == ESubCategory::Wall)
	{
		WallMaterial_HB->AddChildToHorizontalBox(newItemButton);
	}
}

void UCeoDepMenuWidget::AddValuesToButton(Idea* idea)
{
	idea->IdeaButton->GameCover_I->SetColorAndOpacity(idea->CoverColor);
	idea->IdeaButton->IdeaReference = idea;
	idea->IdeaButton->GameTitle_T->SetText(FText::FromString(idea->IdeaName));
	idea->IdeaButton->GameDescription_T->SetText(FText::FromString(idea->IdeaDescription));
	idea->IdeaButton->Genre_T->SetText(Idea::GenreToText(idea->Genre));
	idea->IdeaButton->SuccessChance_T->SetText(FText::AsPercent((idea->SuccessChance + GM->OfficeDepartment->AddedChance) / 100.f));

	idea->IdeaButton->Weight_T->SetText((idea->ProgrammerWorkload > idea->ArtistWorkload) ? FText::FromString("Programmer") : FText::FromString("Artist"));

	if (idea->ProgrammerWorkload == idea->ArtistWorkload)
	{
		idea->IdeaButton->Weight_T->SetText(FText::FromString("All"));
	}

	idea->IdeaButton->BacklogWidget = OfficeDepartment->BacklogWidget;
	idea->IdeaButton->OfficeDepartment = OfficeDepartment;

	idea->IdeaButton->storedIndex = Index;
	idea->IdeaButton->IsFinished = true;
}

void UCeoDepMenuWidget::PublishGame()
{
	PublishGame_Btn->SetIsEnabled(false);
	OfficeDepartment->PublishGame();
}

void UCeoDepMenuWidget::EditPlacedItems()
{
	OfficeDepartment->EditPlacedItems();
}

void UCeoDepMenuWidget::Return()
{
	OfficeDepartment->Return();
}

void UCeoDepMenuWidget::CreateDepartment()
{
	if (Selected == "Marketing")
	{
		for (auto Floor : GM->UnassignedFloorList)
		{
			if (Floor->Flooring == FloorType::Marketing)
			{
				GM->FloorList.Add(Floor);
				GM->UnassignedFloorList.Remove(Floor);
				GM->FloorList[GM->FloorList.Num() - 1]->FloorLevel = GM->FloorList.Num();
				GM->FloorList[GM->FloorList.Num() - 1]->AssignFloorLevel();
				return;
			}
		}
		CreateDep_Btn->SetIsEnabled(false);
	}

	else if (Selected == "Development")
	{
		for (auto Floor : GM->UnassignedFloorList)
		{
			if (Floor->Flooring == FloorType::Dev)
			{
				GM->IsFloorUpgraded = true;
				GM->FloorList.Add(Floor);
				GM->UnassignedFloorList.Remove(Floor);
				GM->FloorList[GM->FloorList.Num() - 1]->FloorLevel = GM->FloorList.Num();
				GM->FloorList[GM->FloorList.Num() - 1]->AssignFloorLevel();
				break;
			}
		}

		for (auto Door : GM->UnassignedDoorList)
		{
			GM->DoorList.Add(Door);
			GM->UnassignedDoorList.Remove(Door);
			GM->DoorList[GM->DoorList.Num() - 1]->FloorLevel = GM->DoorList.Num();
			break;
		}

		for (auto Office : GM->UnassignedOfficeDepartmentList)
		{
			GM->OfficeDepartmentList.Add(Office);
			GM->UnassignedOfficeDepartmentList.Remove(Office);
			GM->OfficeDepartmentList[GM->OfficeDepartmentList.Num() - 1]->FloorLevel = GM->OfficeDepartmentList.Num();
			break;
		}

		for (auto Meeting : GM->UnassignedMeetingDepartmentList)
		{
			GM->MeetingDepartmentList.Add(Meeting);
			GM->UnassignedMeetingDepartmentList.Remove(Meeting);
			GM->MeetingDepartmentList[GM->MeetingDepartmentList.Num() - 1]->FloorLevel = GM->MeetingDepartmentList.Num();
			break;
		}

		for (auto Elevator : GM->UnassignedElevatorList)
		{
			GM->ElevatorList.Add(Elevator);
			GM->UnassignedElevatorList.Remove(Elevator);
			GM->ElevatorList[GM->ElevatorList.Num() - 1]->FloorLevel = GM->ElevatorList.Num();
			break;
		}

		for (auto CEO : GM->OfficeDepartmentList)
		{
			//GM->OfficeDepartmentList[GM->Character->CurrentFloor - 1]->OfficeDepMenuWidget->CreateDep_Btn->SetIsEnabled(false);
			CEO->OfficeDepMenuWidget->CreateDep_Btn->SetIsEnabled(false);
		}
	}
}
