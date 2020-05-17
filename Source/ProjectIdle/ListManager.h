// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Employees/Employee.h"
#include "ListManager.generated.h"

UCLASS()
class PROJECTIDLE_API AListManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AListManager();

	TArray<AChair*> Chairs;

	TArray<AEmployee*> Workers;

	FVector Location;

	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void MoveToMeeting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
