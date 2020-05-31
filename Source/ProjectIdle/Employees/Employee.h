// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\Character.h"
#include "ProjectIdle\EmployeeAIC.h"
#include "Components\WidgetComponent.h"
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
	Programmer			   UMETA(DisplayName = "Programmer"),
	SeniorProgrammer	   UMETA(DisplayName = "Senior"),
	Supervisor             UMETA(DisplayName = "Supervisor")
};

UCLASS()
class PROJECTIDLE_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmployee();

	UPROPERTY(EditAnywhere) ERole Roles;
	UPROPERTY(EditAnywhere) EPosition Position = EPosition::Intern;

	UPROPERTY(EditAnywhere) FText EmployeeName;

	UPROPERTY(EditAnywhere) float Morale = 1;
	UPROPERTY(EditAnywhere) float Performance;
	UPROPERTY(EditAnywhere) float Salary = 200;
	UPROPERTY(EditAnywhere) FString EmployeeRole;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MeetingLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UWidgetComponent* WorkProgressBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AssignedWorkload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentWorkload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AEmployeeAIC* AI;
	//UPROPERTY() float GivenWorkload;

	class UEmployeeSheetWidget* EmployeeSheetWidget;
	//class AAIController* AI;
	//int CurrentWorkload;

	UPROPERTY() FVector StartPosition;
	APlayerCameraManager* Camera;
	UPROPERTY() bool HasWorkStation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool HasWorkload;
	UPROPERTY(BlueprintReadWrite) bool IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsWorking;

	//bool IsMoving;
	//Managers
	class AGameHUD* UI;
	class UGameManager* GM;


	//Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UAnimationAsset* WorkAnim;
	bool HasAnimated = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite) AEmployeeAIC* AI; //custom Cpp AIC ref, unused for now
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GoMeeting();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void ToMeeting(FVector Destination);
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void ReturnPositionAfterMeeting(FVector Destination);
	void BeginWork();

	// Called every frame

	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::RightMouseButton) override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to inputf
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void WorkloadProgress(float Multiplier);
	void Promote();
	void Fire();
};
