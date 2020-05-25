// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Employees/Employee.h"
#include "GameFramework/Actor.h"
#include "Workstation.generated.h"

enum class EType : int16
{
	PROGRAMMER,
	ARTIST
};

UCLASS()
class PROJECTIDLE_API AWorkstation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkstation();
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* DeskMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ComputerMesh;

	UPROPERTY()
	FVector StationLocation;

	class UGameManager* GM;

    EType type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void UpdateWorkstationPosition();
};
