// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IdeaButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UIdeaButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UIdeaButton(const FObjectInitializer& ObjectInitializer);

	class UIdeaBacklogWidget* BacklogWidget;

	int storedIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UGridPanel* GridPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* GameCover_I;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* GameTitle_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* GameDescription_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Genre_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* SuccessChance_T;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Weight_T;
	
public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION() void CallIdeaButton();
};
