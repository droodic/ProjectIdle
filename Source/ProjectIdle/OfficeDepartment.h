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
	class Idea GenerateIdeaValues();
	
	class UGameManager* GM;
	struct FRandomStream random;
	TArray<class Idea*> IdeaList;

	bool IsGenerating;
	
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;
	UPROPERTY(BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(BlueprintReadWrite) float MaxIdeaProgress = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets") TSubclassOf<UUserWidget> UserWidget;
	class UOfficeWidget* OfficeWidget;

//Functions
public:
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void CallMeeting();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
