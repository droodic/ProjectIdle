// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CeoDepMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UCeoDepMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;
	class UGameManager* GM;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Prog_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Artist_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Total_Artist_Btn;
	UPROPERTY() FString Worker;

	virtual void NativeConstruct() override;

private:
	UFUNCTION() void CallHiring();
	UFUNCTION() void CallProgrammerSpawn();
	UFUNCTION() void CallArtistSpawn();
};
