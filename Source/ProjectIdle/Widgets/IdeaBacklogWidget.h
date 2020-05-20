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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* IdeaButton3;
	virtual void NativeConstruct() override;

	void DisplayNewIdea();

};
