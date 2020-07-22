// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	UPROPERTY(BlueprintReadWrite) int ChosenIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* CallMeetingBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Back_Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UScrollBox* IdeaScrollBox;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> IdeaButtonWidgetClass;

public:
	virtual void NativeConstruct() override;
	void DisplayNewIdea(class Idea* idea);
	UFUNCTION() void CallMeeting();
	UFUNCTION() void CallMeeting_M(AFloorManager* ManagerRef);

private:
	UFUNCTION() void Return();
	void SendIdea(int Index);
	void SendIdeaFloorM(int Index);
	void AddValuesToButton(class Idea* idea);
};
