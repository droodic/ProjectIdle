// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "AIModule\Classes\DetourCrowdAIController.h"
#include "ProjectIdle/EmployeeAIC.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/GameHUD.h"
#include "EWorkProgressWidget.h"
#include "Runtime\AIModule\Classes\Blueprint\AIBlueprintHelperLibrary.h"
#include "Engine.h"

// Sets default values
AEmployee::AEmployee()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WorkProgressBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorkloadProgressBar")); //Maybe make Employee BP to set this up, because if later Employee classes emerge if we
	WorkProgressBar->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AEmployee::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->EmployeeList.Add(this);

	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	StartPosition = this->GetActorLocation();
	HasWorkStation = false;
	FVector reset = FVector(0, 0, 278);

	Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	auto WorkloadWidget = WorkProgressBar->GetUserWidgetObject();
	auto WidgetInstance = Cast<UEWorkProgressWidget>(WorkloadWidget);
	WidgetInstance->EmployeeRef = this;
	WorkProgressBar->SetVisibility(false);
}

	//auto AI = Work->Workers[0];
	//auto AI2 = Work->Workers[1];

	/*StartPosition = Work->Workers[0]->GetActorLocation();
	StartPositionTest = Work->Workers[1]->GetActorLocation();
	UE_LOG(LogActor, Warning, TEXT("%s"), *StartPosition.ToString())
	UE_LOG(LogActor, Warning, TEXT("%s"), *StartPositionTest.ToString())*/


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
}

// Called to bind functionality to input
void AEmployee::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEmployee::GoMeeting()
{
	//MoveToLocation(FVector(-710.0, 700.0, 308));


}

void AEmployee::ToMeeting(FVector Destination)
{
	//MoveToLocation(FVector(-710.0, 700.0, 308));
	auto EmployeAI = Cast<AEmployeeAIC>(GetController());
	if (EmployeAI)
	{
		//EmployeAI->MoveToLocation(Destination);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(EmployeAI, Destination);
	}
}

void AEmployee::ReturnPositionAfterMeeting(FVector Destination)
{
	auto EmployeAI = Cast<AEmployeeAIC>(GetController());
	if (EmployeAI)
	{
		//EmployeAI->MoveToLocation(Destination);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(EmployeAI, Destination);
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("%s"), "Null")
	}
}
