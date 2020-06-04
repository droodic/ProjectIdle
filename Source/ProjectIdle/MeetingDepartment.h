// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Workstation.h"
#include "Department.h"
#include "Employees/Employee.h"
#include "MeetingDepartment.generated.h"

UCLASS()
class PROJECTIDLE_API AMeetingDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeetingDepartment();

	FVector OfficeLocation;
	UGameManager* GM;
	bool CanReturn = false;
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void MoveToMeeting();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void BackFromMeeting();

	UPROPERTY(EditAnywhere, Category = "Widgets")TSubclassOf<UUserWidget> UserWidget;
	UPROPERTY() class UMeetingDepWidget* MeetingWidget;
	class Idea* CurrentIdea;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TakeIdea(class Idea* Idea);
	//void TakeIdea(int IdeaIndex);
};
