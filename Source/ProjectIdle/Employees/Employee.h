// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Employee.generated.h"

UCLASS()
class PROJECTIDLE_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmployee();

	UPROPERTY(BlueprintReadOnly) float Happiness;
	UPROPERTY(BlueprintReadOnly) float Performance;
	UPROPERTY(BlueprintReadOnly) float Salary;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
