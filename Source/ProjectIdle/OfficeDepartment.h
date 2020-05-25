// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Department.h"
#include "OfficeDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AOfficeDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	bool IsGenerating;

	class UGameManager* GM;
	class AGameHUD* UI;

	TArray<class Idea*> IdeaList;
	
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxIdeaProgress = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets") TArray<TSubclassOf<UUserWidget>> UserWidgets;

	UPROPERTY() class UCeoDepMenuWidget* OfficeDepMenuWidget; //added in gamehud, get ref from gamehud instead
	UPROPERTY() class UIdeaBacklogWidget* BacklogWidget;


//Functions
public:
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void ViewBacklog();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void CallMeeting();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	 class Idea GenerateIdeaValues();
};
