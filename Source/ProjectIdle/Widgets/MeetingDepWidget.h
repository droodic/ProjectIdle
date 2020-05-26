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
#pragma region ChosenIdea

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* I_GameCover;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameTitle;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_GameDescription;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_SuccessChance;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Weight;

#pragma endregion
	
};
