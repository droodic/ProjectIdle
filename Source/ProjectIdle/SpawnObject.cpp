// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObject.h"
#include "Engine/World.h"
#include "GameManager.h"
#include "Engine.h"

// Sets default values
ASpawnObject::ASpawnObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->Spawning = this;
}

// Called every frame
void ASpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnObject::SpawnWorker()
{
	if (SpawnProgrammer)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;

			FVector SpawnLocation = FVector(0, 0, 270);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			World->SpawnActor<AEmployee>(SpawnProgrammer, SpawnLocation, SpawnRotation, SpawnParameters);
			//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Works");

		}

	}
}

