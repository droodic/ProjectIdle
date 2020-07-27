// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectIdle/SaveableActorInterface.h"
#include "ProjectIdle/InteractableObject.h"
#include "GameFramework/Character.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Employee.generated.h"

UENUM(Meta = (ScriptName = "Role"))
enum class ERole : uint8
{
	Programmer             UMETA(DisplayName = "Programmer"),
	Artist				   UMETA(DisplayName = "Artist"),
	Marketing			   UMETA(DisplayName = "Marketing"),
	Test				   UMETA(DisplayName = "Test"),
	Management			   UMETA(DisplayName = "Management")


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
	Supervisor             UMETA(DisplayName = "Supervisor"),
	FloorManager		   UMETA(DisplayName = "FloorManager")
};

UCLASS()
class PROJECTIDLE_API AEmployee : public ACharacter, public IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmployee();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool IsAtMeeting;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) ERole EmployeeRole;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) EPosition Position = EPosition::Intern;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) FText EmployeeName;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) float Morale = 1;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) float Performance;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) float Salary = 200;
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere) float CostEmployeePromote = 5000;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;

	UPROPERTY() float PromoteToRegular = 20000;
	UPROPERTY() float PromoteToSenior = 50000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MeetingLocation;

	UPROPERTY(SaveGame) int WorkstationPositionRef;
	//class AWorkstation* WorkstationRef;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class USceneCaptureComponent2D* FaceCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class UWidgetComponent* WorkProgressBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) class UWidgetComponent* HelpWidget;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) float AssignedWorkload;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) float CurrentWorkload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AEmployeeAIC* AI;
	//UPROPERTY() float GivenWorkload;

	class Idea* IdeaChance;
	class UEmployeeSheetWidget* EmployeeSheetWidget;
	//class AAIController* AI;
	//int CurrentWorkload;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadWrite) FVector StartPosition;
	APlayerCameraManager* Camera;
	UPROPERTY(SaveGame) bool HasWorkStation;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) bool IsFired = false;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) bool HasWorkload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsWorking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool DefaultEmployee;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) bool HasBeenEvaluated;
	//bool CanInspect = false; //Used for right click ui 

	//bool IsMoving;
	//Managers
	class AGameHUD* UI;
	class UGameManager* GM;
	class AWorkstation* WorkstationRef;

	//Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimSequence* WorkAnim;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimSequence* SitToTypeAnimation;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimSequence* TypeAnimation;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere) UAnimMontage* WorkAnimation;
	bool HasAnimated = false;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* CollisionBox;

	int CompileValueOriginal = 0;
	int CompileValue = 0;
	int NumCompile;

	bool IsDisplaying = false;
	FTimerHandle HelpTimer;
	int RandomHelpNumber;

	UPROPERTY(BlueprintReadWrite) bool NeedAssistance;
	UPROPERTY(SaveGame, EditAnywhere) int Gendre; //0male, 1female
	UPROPERTY(SaveGame, EditAnywhere) int MeshID = 0;

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
	virtual void BeginWork();
	virtual void FiredFinal(); //Called by Door onOverlap
	
	void WorkloadProgress(float Multiplier);
	void Promote();
	void Fire();
	void IsDepartmentWorking();
	void WorkOnTask();
	void AssignSupervisor();
	void StartGetHelp(); //Call Timer start
	UFUNCTION(BlueprintImplementableEvent) void GetGendreName(int GendreID);
	UFUNCTION() void GetHelp(); //Timer Event

	//void OnInteract() override;  //virtual void OnInteract() override;

public:

	// Inherited via IInteractableObject
	virtual void OnInteract();
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Actor")
	//	 void ActorSaveDataLoaded();
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Actor")
	//	 void ActorSaveDataSaved();
};
