// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "Chair.h"
#include "Workstation.h"
#include "Department.h"
#include "Employees/Employee.h"
#include "MeetingDepartment.generated.h"

UCLASS()
class PROJECTIDLE_API AMeetingDepartment : public ADepartment, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeetingDepartment();

	UGameManager* GM;

	FVector OfficeLocation;
	bool CanReturn = false;
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void MoveToMeeting();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void BackFromMeeting();

	UPROPERTY(BlueprintReadWrite) TArray<class AEmployee*> EmployeesAtMeetingList;
	UPROPERTY(EditAnywhere, Category = "Widgets")TSubclassOf<UUserWidget> UserWidget;
	UPROPERTY() class UMeetingDepWidget* MeetingWidget;
	
	class Idea* CurrentIdea;
	TArray<class Idea*> CurrentIdeaList;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool StartingMeetingDep;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnInteract();
	void TakeIdea(class Idea* Idea);
};
