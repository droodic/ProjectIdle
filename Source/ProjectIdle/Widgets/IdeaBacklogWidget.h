// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\UserWidget.h"
#include "IdeaBacklogWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UIdeaBacklogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	class UGameManager* GM;

	class AOfficeDepartment* OfficeDepartment;
	class Idea* newIdea;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Back_Btn;
	
#pragma region IdeaButton1
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* I_GameCover;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameTitle;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameDescription;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_SuccessChance;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Weight;

#pragma endregion

#pragma region IdeaButton2

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* I_GameCover_2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameTitle_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameDescription_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_SuccessChance_2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Weight_2;

#pragma endregion

#pragma region IdeaButton3

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* I_GameCover_3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameTitle_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameDescription_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_SuccessChance_3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Weight_3;

#pragma endregion

public:
	virtual void NativeConstruct() override;

	void DisplayNewIdea();
	void GetIdea(class Idea* idea);

private:
	UFUNCTION() void Back();

public:
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void SendIdea();
};
