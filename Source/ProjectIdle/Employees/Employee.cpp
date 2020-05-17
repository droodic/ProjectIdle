// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "ProjectIdle/ListManager.h"

// Sets default values
AEmployee::AEmployee()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEmployee::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();

	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());

	Work = Cast<AListManager>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Work != nullptr)
	{
		//MeetingLocation = Work->Chairs[0]->ChairLocation;	
		//MoveLoc = Work->Chairs[1]->ChairLocation;
	}
	FVector reset = FVector(0, 0, 278);

	//auto AI = Work->Workers[0];
	//auto AI2 = Work->Workers[1];

	/*StartPosition = Work->Workers[0]->GetActorLocation();
	StartPositionTest = Work->Workers[1]->GetActorLocation();
	UE_LOG(LogActor, Warning, TEXT("%s"), *StartPosition.ToString())
	UE_LOG(LogActor, Warning, TEXT("%s"), *StartPositionTest.ToString())*/

	if (AI != nullptr)
	{
		//AI->SetActorLocation(MeetingLocation);
		//AI2->SetActorLocation(reset);
	}

	//this->SetActorLocation(MeetingLocation);
	//Work->Workers[1]->SetActorLocation(Work->Chairs[1]->ChairLocation);


	//this->SetActorLocation(reset);
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

