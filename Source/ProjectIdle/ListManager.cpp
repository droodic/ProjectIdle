// Fill out your copyright notice in the Description page of Project Settings.


#include "ListManager.h"
#include "EngineUtils.h"

// Sets default values
AListManager::AListManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AListManager::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();
	for (TActorIterator<AChair> It(world, AChair::StaticClass()); It; ++It)
	{
		AChair* chair = *It;
		if (chair != nullptr)
		{
			Chairs.Add(chair);
		}
	}

	//int32 count = Chairs.Num();
	//AChair* chaise = Chairs[0];

	UE_LOG(LogActor, Warning, TEXT("%s"), *Chairs[1]->ChairLocation.ToString())
}

// Called every frame
void AListManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

