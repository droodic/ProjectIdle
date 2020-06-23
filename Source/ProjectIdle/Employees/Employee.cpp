// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "AIModule/Classes/DetourCrowdAIController.h"
#include "Engine.h"
#include "TimerManager.h"
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
#include "ProjectIdle/Widgets/MoneyWidget.h"
#include "ProjectIdle/Widgets/MeetingDepWidget.h"
#include "ProjectIdle/Widgets/EmployeeSheetWidget.h"
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
	//WorkTimer = GetWorldTimerManager();

	if (Position != EPosition::Supervisor) {
		GM->EmployeeList.Add(this);
		switch (EmployeeRole)
		{
		case ERole::Programmer:
			GM->NumOfProgrammers++; //remove later
			GM->ProgrammingDepartment->EmpCount++;
			break;
		case ERole::Artist:
			GM->NumOfArtists++;
			GM->ArtistDepartment->EmpCount++;
			break;
		}
	}
	this->SpawnDefaultController();
	AI = Cast<AEmployeeAIC>(GetController());
	if (!DefaultEmployee) {
		Performance = UKismetMathLibrary::RandomFloatInRange(1.f, 6.f); //make editable constants, cieling value can go higher with upgrades
	}

	HasWorkStation = false;
	FVector reset = FVector(0, 0, 278);//?
	Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (WorkProgressBar != nullptr) {
		auto WorkloadWidget = WorkProgressBar->GetUserWidgetObject();
		auto WidgetInstance = Cast<UEWorkProgressWidget>(WorkloadWidget);
		WidgetInstance->EmployeeRef = this;
		WorkProgressBar->SetVisibility(false);
	}

	if (!Cast<ASupervisor>(this)) {
		//GM->WorkStation->UpdateWorkstationPosition();
		for (auto Workstation : GM->WorkstationList) {
			Workstation->UpdateWorkstationPosition();
		}
		IsDepartmentWorking();
	    MoveEmployee(StartPosition);
	}



}

void AEmployee::IsDepartmentWorking() {
	for (auto Employee : GM->EmployeeList) {
		if (Employee->EmployeeRole == EmployeeRole && Employee->CurrentWorkload > 5.f) {
			Employee->AssignedWorkload /= 2;
			this->AssignedWorkload = Employee->AssignedWorkload;
			this->CurrentWorkload = AssignedWorkload;//Employee->CurrentWorkload / 2;
			Employee->CurrentWorkload /= 2;

			//Recalc Compile values of employee which you are taking workload from
			Employee->NumCompile /= 2;
			Employee->CompileValue = 0;//triggers recalc flag in tick

			BeginWork();
			GEngine->AddOnScreenDebugMessage(12411, 5, FColor::Red, TEXT("Newly hired employee takes part in current department dev"));
			break;
		}
	}
}

void AEmployee::BeginWork() {
	//if compile phase in work
	CompileValue = 0;
	NumCompile = UKismetMathLibrary::RandomIntegerInRange(9, 12);
	//make funciton to find self department and values, example get all department employees number
	for (auto Dep : GM->DepartmentList) {
		if (Dep->DepRole == EmployeeRole) {
			NumCompile = ceil(NumCompile / Dep->EmpCount);
		}
	}

	HasWorkload = true;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEmployee::WorkOnTask, .5f, true);
}

void AEmployee::WorkOnTask() {
	//implement instead of tick way
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

	if (HasWorkload && CurrentWorkload > 0 && !AI->IsMoving && !WorkstationRef->IsCompiling) {
		WorkloadProgress(DeltaTime * ((Performance / 2.5) + (Morale / 5) * GM->SpeedRate));
	}

}

void AEmployee::WorkloadProgress(float Multiplier) {

	/*float SucessChance = GM->MeetingDepartment->CurrentIdea->SuccessChance; /// 100.0f;
	float RateRolled = UKismetMathLibrary::RandomIntegerInRange(0, 100);*/
	//FString SuccessString = FString::SanitizeFloat(SucessChance);
	//UI->MoneyWidget->ShowANotification(SuccessString);

	//FString RateString = FString::SanitizeFloat(RateRolled);
	//UI->MoneyWidget->ShowANotification(RateString);

	//Test function - Workers reduce workloads, make function / use timer +event instead of tick
	if (!IsWorking && WorkAnimation != nullptr) {
		FRotator AdjustRotate = FRotator(0, 90, 0);
		SetActorRotation(WorkstationRef->ChairMesh->GetComponentRotation() + AdjustRotate);
		WorkProgressBar->SetVisibility(true);
		IsWorking = true;
	}
	if (WorkProgressBar != nullptr) {
		WorkProgressBar->SetWorldRotation(Camera->GetCameraRotation());
		WorkProgressBar->AddLocalRotation(FRotator(0, 180, 0));
	}

	if (CompileValue == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Assigned workload:" + FString::FromInt(AssignedWorkload));

		if (NumCompile == 1) {
			NumCompile = 3; //min 3 compile ? , Figure out better way of dividing number of compiles on new hire
		}
		CompileValueOriginal = (AssignedWorkload / NumCompile);
		CompileValue = CompileValueOriginal;
		/*GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "NumCompile:" + FString::FromInt(NumCompile));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Compile value original:" + FString::FromInt(CompileValueOriginal));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, "Current Workload:" + FString::FromInt(CurrentWorkload));
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, "Next Compile at : " + FString::FromInt(AssignedWorkload - CompileValueOriginal));*/

		if (CurrentWorkload <= AssignedWorkload - CompileValueOriginal) {
			//Under exact compile range, force compile
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Forcing compile");
			WorkstationRef->DoCompile();
			CompileValue += CompileValueOriginal; //+1 to stop from 100% compiling at 0 workload
			NumCompile--;
		}
	}
	if (CompileValue != 0 && (int)CurrentWorkload == (int)(AssignedWorkload - CompileValue) && NumCompile > 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Compiling");
		WorkstationRef->DoCompile();

		CompileValue += CompileValueOriginal; //+1 to stop from 100% compiling at 0 workload
		NumCompile--;
	}
	else {
		CurrentWorkload -= Multiplier;
	}


	if (CurrentWorkload <= 0) {
		//Self workload finished, check to see if others remain. If others in same department remain, go to them, and take 50% of their remainding workload if there's more than 10 seconds left of WL
		//If none remain, give player money if idea was successful
		for (auto AnEmployee : GM->EmployeeList) {
			auto ThisEmployeeAI = Cast<AAIController>(GetController());
			if (EmployeeRole == ERole::Programmer && AnEmployee->EmployeeRole == ERole::Programmer) {
				if (AnEmployee->CurrentWorkload >= 15) {//change to editor editable constant 
					AnEmployee->CurrentWorkload /= 2;
					CurrentWorkload += AnEmployee->CurrentWorkload / 2;
					GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Programmer workload finished, taking workload from another employee"));
					break;

				}
			}

			else if (EmployeeRole == ERole::Artist && AnEmployee->EmployeeRole == ERole::Artist) {
				if (AnEmployee->CurrentWorkload >= 15) {
					AnEmployee->CurrentWorkload /= 2;
					CurrentWorkload += AnEmployee->CurrentWorkload / 2;
					GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Artist workload finished, taking workload from another employee"));
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
			//UIdeaButton::IsInProduction = false;
			GM->IdeaInProduction = false;
			GM->OfficeDepartment->OfficeDepMenuWidget->GetFinishedIdea(GM->MeetingDepartment->CurrentIdea);
			UI->MoneyWidget->ShowANotification("PRODUCTION OF A GAME FINISHED, WAITING FOR BEING PUBLISHED");
			CompileValue = 0;
			//if (SucessChance >= RateRolled)
			//{
			//	UI->MoneyWidget->ShowANotification("PRODUCTION OF A GAME FINISHED, WAITING FOR BEING PUBLISHED");
			//}
			//else
			//{
			//	UI->MoneyWidget->ShowANotification("Sorry failed");
			//}

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

			GM->Money -= CostEmployeePromote;
			CostEmployeePromote = PromoteToRegular;

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

void AEmployee::MoveEmployee(FVector Destination, float AcceptanceRadius)
{
	if (AI)
	{
		auto LookAtRotator = FRotator(UKismetMathLibrary::MakeRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Destination).Yaw));
		UKismetMathLibrary::BreakRotator(LookAtRotator, LookAtRotator.Roll, LookAtRotator.Pitch, LookAtRotator.Yaw);
		SetActorRotation(LookAtRotator);
		AI->MoveToLocation(Destination, AcceptanceRadius);
		AI->IsMoving = true;
		//Make all this moving stuff, lookat, IsMoving, into 1 function
	}
}

void AEmployee::AssignSupervisor()
{
	for (int i = 0; i < GM->WorkstationList.Num(); i++)
	{
		if (GM->WorkstationList[i]->StationRole == this->EmployeeRole && GM->WorkstationList[i]->StationOwnerPosition == this->Position)
		{
			this->StartPosition = GM->WorkstationList[i]->StationLocation;
			this->WorkstationRef = GM->WorkstationList[i];
			this->HasWorkStation = true;
			GM->WorkstationList[i]->HasEmployee = true;
		}
	}
	MoveEmployee(StartPosition);
}

//void AEmployee::ActorSaveDataLoaded()
//{
//}
//
//void AEmployee::ActorSaveDataSaved()
//{
//}

