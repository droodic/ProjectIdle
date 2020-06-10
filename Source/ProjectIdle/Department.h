// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "ProjectIdleCharacter.h"
#include "GameFramework/Actor.h"
#include "Employees/Supervisor.h"
#include "Department.generated.h"

UCLASS()
class PROJECTIDLE_API ADepartment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int DepartmentCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int EmpCount; //convert GM dep emp count to here eventually, for now unused
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;

	ADepartment();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool HasSupervisor = false;
	ERole DepRole;
	class UGameManager* GM;
	ASupervisor* SupervisorRef;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
