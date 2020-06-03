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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UScrollBox* IdeaScrollBox;
	class UIdeaButton* IdeaButton;
	TArray<class UIdeaButton*> IdeaButtonList;
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UIdeaButton* IdeaButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Prog_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Hire_Artist_Btn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Total_Artist_Btn;
	UPROPERTY() FString Worker;

	
public:
	virtual void NativeConstruct() override;
	void GetIdea(class Idea* idea);

private:
	UFUNCTION() void CallHiring();
	UFUNCTION() void CallProgrammerSpawn();
	UFUNCTION() void CallArtistSpawn();
	UFUNCTION() void ActiveWorkstation(int Number);

	void AddValuesToButton(class UIdeaButton* button, class Idea* idea);

};
