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
	AOfficeDepartment();
	class Idea GenerateIdeaValues();
	
	class UGameManager* GM;
	struct FRandomStream random;
	TArray<class Idea*> IdeaList;

	bool IsGenerating;
	
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxIdeaProgress = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets") TArray<TSubclassOf<UUserWidget>> UserWidgets;
	class UCeoDepMenuWidget* OfficeDepMenuWidget;
	class UOfficeWidget* OfficeWidget;

//Functions
public:
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void CallMeeting();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
