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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* T_Genre;
	
};
