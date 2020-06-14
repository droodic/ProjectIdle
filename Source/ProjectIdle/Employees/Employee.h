// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "ProjectIdle/EmployeeAIC.h"
#include "Components/WidgetComponent.h"
#include "Employee.generated.h"

UENUM(Meta = (ScriptName = "Role"))
enum class ERole : uint8
{
	Programmer             UMETA(DisplayName = "Programmer"),
	Artist				   UMETA(DisplayName = "Artist")
};

UENUM(Meta = (ScriptName = "Position"))
enum class EPosition : uint8
{
	Intern				   UMETA(DisplayName = "Intern"),
	Junior				   UMETA(DisplayName = "Junior"),
	Regular				   UMETA(DisplayName = "Regular"),
	Senior			       UMETA(DisplayName = "Senior"),
	//Programmer			   UMETA(DisplayName = "Programmer"),
	//Artist			       UMETA(DisplayName = "Artist"),
	//SeniorProgrammer	   UMETA(DisplayName = "Senior"),
	//SeniorArtist 	       UMETA(DisplayName = "Senior"),
	Supervisor             UMETA(DisplayName = "Supervisor")
};

UCLASS()
class PROJECTIDLE_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmployee();

	UPROPERTY(EditAnywhere) ERole EmployeeRole;
	UPROPERTY(EditAnywhere) EPosition Position = EPosition::Intern;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FText EmployeeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Morale = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Performance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Salary = 200;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float CostEmployeePromote = 5000;

	UPROPERTY() float PromoteToRegular = 20000;
	UPROPERTY() float PromoteToSenior = 50000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MeetingLocation;

	UPROPERTY() int WorkstationPositionRef;
	//class AWorkstation* WorkstationRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UWidgetComponent* WorkProgressBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AssignedWorkload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentWorkload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AEmployeeAIC* AI;
	//UPROPERTY() float GivenWorkload;

	class Idea* IdeaChance;
	class UEmployeeSheetWidget* EmployeeSheetWidget;
	//class AAIController* AI;
	//int CurrentWorkload;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) FVector StartPosition;
	APlayerCameraManager* Camera;
	UPROPERTY() bool HasWorkStation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsFired = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool HasWorkload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsWorking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool DefaultEmployee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool HasBeenEvaluated;
	bool CanInspect = false; //Used for right click ui 

	//bool IsMoving;
	//Managers
	class AGameHUD* UI;
	class UGameManager* GM;
	class AWorkstation* WorkstationRef;

	//Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimSequence* WorkAnimation;
	bool HasAnimated = false;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::RightMouseButton) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void MoveEmployee(FVector Destination, float AcceptanceRadius = 0.f);
	void BeginWork();
	void WorkloadProgress(float Multiplier);
	void Promote();
	void Fire();
	virtual void FiredFinal(); //Called by Door onOverlap
	void IsDepartmentWorking();
};
