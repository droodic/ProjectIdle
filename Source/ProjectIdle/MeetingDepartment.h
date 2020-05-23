// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "ProjectIdle/GameManager.h"
#include "Employees/Employee.h"
#include "MeetingDepartment.generated.h"

UCLASS()
class PROJECTIDLE_API AMeetingDepartment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeetingDepartment();
	 //Move this to game manager if need a clean global reference
	//TArray<AChair*> Chairs;

	//TArray<AEmployee*> Workers;

	FVector OfficeLocation;

	UGameManager* GM;

	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void MoveToMeeting();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void BackFromMeeting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
