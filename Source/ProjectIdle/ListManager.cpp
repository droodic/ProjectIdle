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
	GM = GetWorld()->GetGameInstance<UGameManager>();
	
	UWorld* world = GetWorld();
	for (TActorIterator<AChair> It(world, AChair::StaticClass()); It; ++It)
	{
		AChair* chair = *It;
		if (chair != nullptr)
		{
			Chairs.Add(chair);
		}
	}

	for (TActorIterator<AEmployee> It(world, AEmployee::StaticClass()); It; ++It)
	{
		AEmployee* worker = *It;
		if (worker != nullptr)
		{
			Workers.Add(worker);
		}
	}

	//Testing employee and chair array

	//int32 count = Chairs.Num();
	//AChair* chaise = Chairs[0];
	//AEmployee* man = Workers[0];
	//AEmployee* mans = Workers[1];
	//AEmployee* man3 = Workers[2];
	//int32 size = Workers.Num();
	//FString sizeString = FString::FromInt(size);


	//man->ToMeeting(chaise->ChairLocation);

	//UE_LOG(LogActor, Warning, TEXT("%s"), *chaise->ChairLocation.ToString())
	//UE_LOG(LogActor, Warning, TEXT("%s"), *sizeString)

	//UE_LOG(LogActor, Warning, TEXT("%s"), *man->StartPosition.ToString())
	//UE_LOG(LogActor, Warning, TEXT("%s"), *mans->StartPosition.ToString())
	//UE_LOG(LogActor, Warning, TEXT("%s"), *man3->StartPosition.ToString())

    //End of test
	MoveToMeeting();
}

// Called every frame
void AListManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AListManager::MoveToMeeting()
{
	int32 chairSize = Chairs.Num();
	int32 employeeSize = Workers.Num();
	for (int i = 0; i < chairSize; i++)
	{
		AEmployee* man = Workers[i];
		AChair* chaise = Chairs[i];
		man->ToMeeting(chaise->ChairLocation);
	}
}
