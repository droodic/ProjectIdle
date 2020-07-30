// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Employees/Employee.h"
#include "CeoDepMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UCeoDepMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) class UGameManager* GM;

	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UScrollBox* IdeaScrollBox;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> IdeaButtonWidgetClass;
	
//	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* SaveGame_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* PublishGame_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_FloorManager_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Prog_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Artist_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_ProgSup_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_ArtistSup_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Total_Artist_Btn;

	//Load Game Notificator Bindings
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UCanvasPanel* LoadGameCanvas;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_CompanyName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_TimePast;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_NumIdeas;

	UPROPERTY(meta = (BindWidget)) class UButton* EditPlacedItems_Btn;
	UPROPERTY(meta = (BindWidget)) class UButton* Return_Btn;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* IdeaGeneratedMoney_T;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* IdeaStadistics_T;
	UPROPERTY() FString Worker;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UBorder* NewItem_Border;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* CreateDep_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UComboBoxString* SelectComboBox;
	UPROPERTY(BlueprintReadWrite) FString Selected = "Development";

	int Index = 0;
	int ChosenIndex;

#pragma region InventoryPanel
	UPROPERTY(meta = (BindWidget)) class UWrapBox* OfficeDecoration_WB;
	UPROPERTY(meta = (BindWidget)) class UHorizontalBox* FloorMaterial_HB;
	UPROPERTY(meta = (BindWidget)) class UHorizontalBox* WallMaterial_HB;
	UPROPERTY(meta = (BindWidget)) class UImage* CurrentFloorMat_I;
	UPROPERTY(meta = (BindWidget)) class UImage* CurrentWallMat_I;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> InventoryButtonWidgetClass;

#pragma endregion

public:
	virtual void NativeConstruct() override;
	void GetFinishedIdea(class Idea* idea);
	void AddItemToInventory(class AItem* item);
	UFUNCTION() void ActivateWorkstation(enum ERole StationRole, enum EPosition OwnerPosition, bool IsSupervisor);
	UFUNCTION() void ClearFinishedGames();
	UFUNCTION() void CreateDepartment();
	//UFUNCTION() void Display

private:
	UFUNCTION() void CallHiring();
	UFUNCTION() void CallProgrammerSpawn();
	UFUNCTION() void CallProgrammerSupSpawn();
	UFUNCTION() void CallArtistSpawn();
	UFUNCTION() void CallArtistSupSpawn();
	UFUNCTION() void CallFloorManagerSpawn();
	UFUNCTION() void PublishGame();
	UFUNCTION() void EditPlacedItems();
	UFUNCTION() void Return();

	void AddValuesToButton(class Idea* idea);
};
