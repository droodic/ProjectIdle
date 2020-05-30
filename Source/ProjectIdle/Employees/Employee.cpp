// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "AIModule\Classes\DetourCrowdAIController.h"
#include "ProjectIdle/EmployeeAIC.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/GameHUD.h"
#include "EWorkProgressWidget.h"
#include "Runtime\AIModule\Classes\Blueprint\AIBlueprintHelperLibrary.h"
#include "Runtime\Engine\Classes\Kismet\KismetMathLibrary.h"
#include "Engine.h"

// Sets default values
AEmployee::AEmployee()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorkProgressBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorkloadProgressBar")); //Maybe make Employee BP to set this up, because if later Employee classes emerge if we
	WorkProgressBar->AttachTo(RootComponent);
	WorkProgressBar->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	

}

// Called when the game starts or when spawned
void AEmployee::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->EmployeeList.Add(this);

	//Find better way maybe, enum? 
	if (EmployeeRole == "Artist") {
		GM->NumOfArtists++;
	}
	else if (EmployeeRole == "Programmer") {
		GM->NumOfProgrammers++;
	}

	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	StartPosition = this->GetActorLocation();
	HasWorkStation = false;
	FVector reset = FVector(0, 0, 278);
	this->SpawnDefaultController();
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
	
	int32 number = GM->EmployeeList.Num();

	FString sizeString = FString::FromInt(number);
	UE_LOG(LogActor, Warning, TEXT("%s"), *sizeString)

}




void AEmployee::BeginWork() {
	IsWorking = true;
}

void AEmployee::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (UI != nullptr) {

		UI->ShowEmployeeSheet(this);
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Employee is Clicked, UI Is null!"));
	}
}
// Called every frame
void AEmployee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//add a if enabled condition or smth

	if (WorkProgressBar != nullptr) {
		WorkProgressBar->SetWorldRotation(Camera->GetCameraRotation());
		WorkProgressBar->AddLocalRotation(FRotator(0, 180, 0));
	}


	//Test function - Workers reduce workloads, make function / use timer +event instead of tick
	if (IsWorking && CurrentWorkload > 0) {
		CurrentWorkload -= (DeltaTime * (Performance / 2));
		if (CurrentWorkload <= 0) {
			//Self workload finished, check to see if others remain. If others in same department remain, go to them, and take 50% of their remainding workload if there's more than 10 seconds left of WL
			//If none remain, give player money if idea was successful
			for (auto AnEmployee : GM->EmployeeList) {
				auto ThisEmployeeAI = Cast<AAIController>(GetController());
				if (EmployeeRole == "Programmer" && AnEmployee->EmployeeRole == "Programmer") {
					if (AnEmployee->CurrentWorkload >= 5) {//change to editor editable constant 
						//ThisEmployeeAI->MoveToLocation(AnEmployee->GetActorLocation(), 30.f);

						AnEmployee->CurrentWorkload /= 2;
						CurrentWorkload += AnEmployee->CurrentWorkload / 2;
						//ReturnPositionAfterMeeting(StartPosition);
						GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Programmer workload finished, taking workload from another employee"));
						break;

					}
				}

				else if (EmployeeRole == "Artist" && AnEmployee->EmployeeRole == "Artist") {
					if (AnEmployee->CurrentWorkload >= 5) {

						//ThisEmployeeAI->MoveToLocation(AnEmployee->GetActorLocation(), 30.f);
						//auto Distance = FVector::Dist(GetActorLocation(), AnEmployee->GetActorLocation());
						//while (Distance > 10.f) {
						//	Distance = FVector::Dist(GetActorLocation(), AnEmployee->GetActorLocation());

						//}

						AnEmployee->CurrentWorkload /= 2;
						CurrentWorkload += AnEmployee->CurrentWorkload / 2;
						//ReturnPositionAfterMeeting(StartPosition);
						GEngine->AddOnScreenDebugMessage(210, 5, FColor::Emerald, TEXT("Programmer workload finished, taking workload from another employee"));
						break;
					}
				}
			}

		}
		if (CurrentWorkload <= 0) { //Change to condition checking if all other employee are also done, then prepare to give money
			IsWorking = false;
			WorkProgressBar->SetVisibility(false);

			bool isOver = true;
			for (auto AnEmployee : GM->EmployeeList) {
				if (AnEmployee->IsWorking == true) {
					isOver = false;
				}

			}
			if (isOver == true) {

				GM->Money += 10000; //Use algo later, and do real way of assgning money
			}

		}
	}
}



// Called to bind functionality to input
void AEmployee::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEmployee::Promote()
{
	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Green, TEXT("Promote button called"));

	//EPosition(1);
	switch (Position)
	{
	case EPosition::Intern:
		Position = EPosition::Junior;
		Salary += 200;
		break;
	case EPosition::Junior:
		Position = EPosition::Programmer;
		Salary += 200;
		break;
	case EPosition::Programmer:
		Position = EPosition::SeniorProgrammer;
		Salary += 200;
		break;
	case EPosition::SeniorProgrammer:
		Salary += 100;
		break;
	}
}

void AEmployee::Fire()
{
}

void AEmployee::GoMeeting()
{
	//MoveToLocation(FVector(-710.0, 700.0, 308));


}

void AEmployee::ToMeeting(FVector Destination)
{
	//MoveToLocation(FVector(-710.0, 700.0, 308));
	auto EmployeAI = Cast<AAIController>(GetController());
	if (EmployeAI)
	{
		auto LookAtRotator = FRotator(UKismetMathLibrary::MakeRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Destination).Yaw));
		UKismetMathLibrary::BreakRotator(LookAtRotator, LookAtRotator.Roll, LookAtRotator.Pitch, LookAtRotator.Yaw);
		SetActorRotation(LookAtRotator);
		EmployeAI->MoveToLocation(Destination);
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("%s"), "Null")
	}
}

void AEmployee::ReturnPositionAfterMeeting(FVector Destination)
{
	auto EmployeAI = Cast<AAIController>(GetController());
	if (EmployeAI)
	{
		auto LookAtRotator = FRotator(UKismetMathLibrary::MakeRotator(0, 0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Destination).Yaw));
		UKismetMathLibrary::BreakRotator(LookAtRotator, LookAtRotator.Roll, LookAtRotator.Pitch, LookAtRotator.Yaw);
		SetActorRotation(LookAtRotator);
		EmployeAI->MoveToLocation(Destination);
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(EmployeAI, Destination);
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("%s"), "Null")
	}
}

