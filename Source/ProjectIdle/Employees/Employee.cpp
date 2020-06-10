// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "AIModule/Classes/DetourCrowdAIController.h"
#include "Engine.h"
#include "EWorkProgressWidget.h"
#include "ProjectIdle/Idea.h"
#include "ProjectIdle/EmployeeAIC.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/Workstation.h"
#include "ProjectIdle/GameHUD.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/MeetingDepartment.h"
#include "ProjectIdle/CeoDepMenuWidget.h"
#include "ProjectIdle/ProjectIdleCharacter.h"
#include "ProjectIdle/Widgets/IdeaButton.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values
AEmployee::AEmployee()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorkProgressBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorkloadProgressBar")); //Maybe make Employee BP to set this up, because if later Employee classes emerge if we
	WorkProgressBar->AttachTo(RootComponent);
	WorkProgressBar->SetVisibility(false);
	WorkProgressBar->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	CollisionBox->AttachTo(RootComponent);
	CollisionBox->SetBoxExtent(FVector(350, 350, 350));
}

// Called when the game starts or when spawned
void AEmployee::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());

	Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (Position != EPosition::Supervisor) {
		GM->EmployeeList.Add(this);
		switch (EmployeeRole)
		{
		case ERole::Programmer:
			GM->NumOfProgrammers++;
			break;
		case ERole::Artist:
			GM->NumOfArtists++;
			break;
		}
	}
	this->SpawnDefaultController();
	AI = Cast<AEmployeeAIC>(GetController());
	//UDataTable
	if (!DefaultEmployee) {
		Performance = UKismetMathLibrary::RandomFloatInRange(1.f, 6.f); //make editable constants, cieling value can go higher with upgrades
	}

	HasWorkStation = false;
	FVector reset = FVector(0, 0, 278);
	Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (WorkProgressBar != nullptr) {
		auto WorkloadWidget = WorkProgressBar->GetUserWidgetObject();
		auto WidgetInstance = Cast<UEWorkProgressWidget>(WorkloadWidget);
		WidgetInstance->EmployeeRef = this;
		WorkProgressBar->SetVisibility(false);
	}
	if (EmployeeSheetWidget)
	{
		EmployeeSheetWidget->Employee = this;
	}

	if (!Cast<ASupervisor>(this)) {
		GM->WorkStation->UpdateWorkstationPosition();
	}

	MoveEmployee(StartPosition);
	IsDepartmentWorking();

}

void AEmployee::IsDepartmentWorking() {
	for (auto Employee : GM->EmployeeList) {
		if (Employee->EmployeeRole == EmployeeRole && Employee->CurrentWorkload > 5.f) {
			Employee->AssignedWorkload /= 2;
			this->AssignedWorkload = Employee->AssignedWorkload;
			this->CurrentWorkload = Employee->CurrentWorkload / 2;
			Employee->CurrentWorkload /= 2;
			BeginWork();
			GEngine->AddOnScreenDebugMessage(12411, 5, FColor::Red, TEXT("Newly hired employee takes part in current department dev"));
			break;
		}
	}
}

void AEmployee::BeginWork() {
	HasWorkload = true;
}

void AEmployee::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (UI != nullptr && CanInspect) {

		UI->ShowEmployeeSheet(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("Employee is Clicked, UI Is null!"));
	}
}

// Called every frame
void AEmployee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//add a if enabled condition or smth

	if (HasWorkload && CurrentWorkload > 0 && !AI->IsMoving) {
		WorkloadProgress(DeltaTime * ((Performance / 2) + (Morale / 5)));
	}

}

void AEmployee::WorkloadProgress(float Multiplier) {
	//Test function - Workers reduce workloads, make function / use timer +event instead of tick
	if (WorkProgressBar != nullptr) {
		WorkProgressBar->SetWorldRotation(Camera->GetCameraRotation());
		WorkProgressBar->AddLocalRotation(FRotator(0, 180, 0));
	}

	//remove isworking once ismoving is implement? && !AI->IsMoving
	if (!IsWorking && WorkAnim != nullptr) {

		//auto LookAtRotator = FRotator(UKismetMathLibrary::MakeRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GM->WorkstationList[WorkstationPositionRef]->ChairMesh->GetComponentRotation()).Yaw));
		//UKismetMathLibrary::BreakRotator(LookAtRotator, LookAtRotator.Roll, LookAtRotator.Pitch, LookAtRotator.Yaw);
		SetActorRotation(GM->WorkstationList[WorkstationPositionRef]->ChairMesh->GetComponentRotation());
		//GetMesh()->PlayAnimation(WorkAnim, false);
		WorkProgressBar->SetVisibility(true);
		IsWorking = true;
	}

	CurrentWorkload -= Multiplier;
	if (CurrentWorkload <= 0) {
		//Self workload finished, check to see if others remain. If others in same department remain, go to them, and take 50% of their remainding workload if there's more than 10 seconds left of WL
		//If none remain, give player money if idea was successful
		for (auto AnEmployee : GM->EmployeeList) {
			auto ThisEmployeeAI = Cast<AAIController>(GetController());
			if (EmployeeRole == ERole::Programmer && AnEmployee->EmployeeRole == ERole::Programmer) {
				if (AnEmployee->CurrentWorkload >= 5) {//change to editor editable constant 
					AnEmployee->CurrentWorkload /= 2;
					CurrentWorkload += AnEmployee->CurrentWorkload / 2;
					GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Programmer workload finished, taking workload from another employee"));
					break;

				}
			}

			else if (EmployeeRole == ERole::Artist && AnEmployee->EmployeeRole == ERole::Artist) {
				if (AnEmployee->CurrentWorkload >= 5) {
					AnEmployee->CurrentWorkload /= 2;
					CurrentWorkload += AnEmployee->CurrentWorkload / 2;
					GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Programmer workload finished, taking workload from another employee"));
					break;
				}
			}
		}

	}
	if (CurrentWorkload <= 0) { //Change to condition checking if all other employee are also done, then prepare to give money
		HasWorkload = false;
		WorkProgressBar->SetVisibility(false);
		//go back to regular animation ?
		IsWorking = false;
		bool isOver = true;
		for (auto AnEmployee : GM->EmployeeList)
		{
			if (AnEmployee->HasWorkload == true)
			{
				isOver = false;
			}
		}
		if (isOver == true)
		{
			UIdeaButton::IsInProduction = false;
			GM->OfficeDepartment->OfficeDepMenuWidget->GetFinishedIdea(GM->MeetingDepartment->CurrentIdea);
			//GM->Money += UKismetMathLibrary::RandomIntegerInRange(15000, 25000); //Use algo later, and do real way of assgning money
		}
	}
}

// Called to bind functionality to input
void AEmployee::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEmployee::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr) {
		CanInspect = true;
	}
}

void AEmployee::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr) {
		CanInspect = false;
		if (UI->EmpSheetWidget->IsInViewport())
		{
			UI->EmpSheetWidget->RemoveFromViewport();
		}
	}
}

void AEmployee::Promote()
{
	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Green, "Promote button called");
	float AddMorale = FMath::FRandRange(.25f, .75f);

	if (GM->Money >= CostEmployeePromote)
	{

		//float AddMorale = FMath::FRandRange(1, 10);
		GEngine->AddOnScreenDebugMessage(2, 5, FColor::Green, FString::Printf(TEXT("Number: x: %f"), AddMorale));
		switch (Position)
		{
		case EPosition::Intern:
			Position = EPosition::Junior;
			Salary += 200;
			if (Morale < 10) {
				Morale += AddMorale + 0.5f;
				if (Morale >= 10) {
					Morale = 10;
				}
			}

			CostEmployeePromote = PromoteToRegular;
			GM->Money -= CostEmployeePromote;

			break;
		case EPosition::Junior:
			Position = EPosition::Regular;
			Salary += 200;
			if (Morale < 10) {

				Morale += AddMorale + 1.f;
				if (Morale >= 10) {
					Morale = 10;
				}
			}
			GM->Money -= CostEmployeePromote;
			CostEmployeePromote = PromoteToSenior;
			break;
		case EPosition::Regular:
			Position = EPosition::Senior;
			Salary += 200;
			if (Morale < 10) {
				Morale += AddMorale + 2.5f;
				if (Morale >= 10) {
					Morale = 10;
				}
			}
			GM->Money -= CostEmployeePromote;
			break;
			//case EPosition::SeniorProgrammer:
			//	Salary += 100;
			//	if (Morale < 10) {

			//		Morale += AddMorale;
			//		if (Morale >= 10) {
			//			Morale = 10;
			//		}
			//	}
			//	GM->Money -= PromoteToSenior;
			//	break;
			//}
		}

		UI->RefreshEmployeeSheet(this);
	}
}

void AEmployee::Fire()
{
	IsFired = true;
	//Redistr workload
	if (CurrentWorkload > 0) {
		for (auto DepartmentEmp : GM->EmployeeList) {
			if (DepartmentEmp->EmployeeRole == EmployeeRole) {
				DepartmentEmp->CurrentWorkload += CurrentWorkload;
				DepartmentEmp->AssignedWorkload += CurrentWorkload;
				//CurrentWorkload = 0;
				WorkProgressBar->SetVisibility(false);
				IsWorking = false;
			}
		}
	}

	MoveEmployee(GM->Door->GetActorLocation());
}

void AEmployee::FiredFinal()
{
	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red, "The employee is Fired!");
	if (Position != EPosition::Supervisor) {
		if (this->EmployeeRole == ERole::Programmer)
		{
			GM->NumOfProgrammers--;
		}
		if (this->EmployeeRole == ERole::Artist)
		{
			GM->NumOfArtists--;
		}
	GM->WorkstationList[this->WorkstationPositionRef]->HasEmployee = false;
	}

	GM->EmployeeList.Remove(this);
	UI->CloseEmployeeSheet();
	this->Destroy();
}

void AEmployee::MoveEmployee(FVector Destination)
{
	if (AI)
	{
		auto LookAtRotator = FRotator(UKismetMathLibrary::MakeRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Destination).Yaw));
		UKismetMathLibrary::BreakRotator(LookAtRotator, LookAtRotator.Roll, LookAtRotator.Pitch, LookAtRotator.Yaw);
		SetActorRotation(LookAtRotator);
		AI->MoveToLocation(Destination);
		AI->IsMoving = true;
		//Make all this moving stuff, lookat, IsMoving, into 1 function
	}
}


