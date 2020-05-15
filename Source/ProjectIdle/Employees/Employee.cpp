// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"

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

	UI = Cast <class AGameHUD* > (UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	
}

void AEmployee::NotifyActorOnClicked(FKey ButtonPressed)
{
	UI->ShowEmployeeSheet(this);
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

