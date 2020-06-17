// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeetingDepWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UMeetingDepWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	class UGameManager* GM;
	class AGameHUD* UI;
	//class AMeetingDepartment* MeetingDep;

	//UPROPERTY() float SpeedRate = 1;
#pragma region ChosenIdea
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UComboBoxString* ApproachComboBox;
	UPROPERTY(BlueprintReadWrite) FString SelectedApproach = "Default";

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* I_GameCover;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameTitle;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameDescription;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_SuccessChance;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Weight;

#pragma endregion
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* StartMeetingBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Perfectionist_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* CrunchTime_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Default_Btn;


	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void StartMeeting();




private:
	virtual void NativeConstruct() override;
	
};
