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
	class UGameManager* GM;

	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UScrollBox* IdeaScrollBox;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> IdeaButtonWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* PublishGame_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Prog_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Artist_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_ProgSup_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_ArtistSup_Btn;
	UPROPERTY(meta = (BindWidget)) class UButton* Return_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Total_Artist_Btn;
	UPROPERTY() FString Worker;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* CreateDep_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UComboBoxString* SelectComboBox;
	UPROPERTY(BlueprintReadWrite) FString Selected = "Marketing";

	


	int Index = 0;
	int ChosenIndex;

public:
	virtual void NativeConstruct() override;
	void GetFinishedIdea(class Idea* idea);
	UFUNCTION() void ActivateWorkstation(ERole StationRole, EPosition OwnerPosition, bool IsSupervisor);

private:
	UFUNCTION() void CallHiring();
	UFUNCTION() void CallProgrammerSpawn();
	UFUNCTION() void CallProgrammerSupSpawn();
	UFUNCTION() void CallArtistSpawn();
	UFUNCTION() void CallArtistSupSpawn();
	UFUNCTION() void PublishGame();
	UFUNCTION() void Return();
	void AddValuesToButton(class Idea* idea);
};
