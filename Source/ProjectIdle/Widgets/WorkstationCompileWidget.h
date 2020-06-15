// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectIdle/Workstation.h"
#include "WorkstationCompileWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UWorkstationCompileWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite) class AWorkstation* WorkstationRef;
};
