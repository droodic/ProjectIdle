// Fill out your copyright notice in the Description page of Project Settings.


#include "ListManager.h"
#include "EngineUtils.h"

// Sets default values
AListManager::AListManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OfficeLocation = FVector(-720.0, 900, 200);
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
	//AChair* chaise1 = Chairs[1];
	//AEmployee* man = Workers[0];
	//AEmployee* mans = Workers[1];
	//AEmployee* man3 = Workers[2];
	//int32 size = Workers.Num();
	//FString sizeString = FString::FromInt(size);


     // UE_LOG(LogActor, Warning, TEXT("%s"), *chaise->GetActorLocation().ToString())
	//UE_LOG(LogActor, Warning, TEXT("%s"), *chaise1->GetActorLocation().ToString())

	//UE_LOG(LogActor, Warning, TEXT("%s"), *sizeString)

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
	int32 LoopUntil;
	bool MoreEmployeeThanChair = false;

	if (chairSize > employeeSize)
	{
		LoopUntil = chairSize - employeeSize;
	}
	else if(employeeSize > chairSize)
	{
		//If there too many employee
		MoreEmployeeThanChair = true;
		LoopUntil = employeeSize;
	}
	else
	{
		LoopUntil = chairSize;
	}

	for (int i = 0; i < LoopUntil; i++)
	{
		if (MoreEmployeeThanChair)
		{
			if (i < employeeSize - chairSize)
			{
				AEmployee* man = Workers[i];
				AChair* chaise = Chairs[i];
				man->ToMeeting(chaise->GetActorLocation());
			}
			else
			{
				AEmployee* man = Workers[i];
				man->ToMeeting(OfficeLocation);
			}
		}
		else
		{
			AEmployee* man = Workers[i];
			AChair* chaise = Chairs[i];
			man->ToMeeting(chaise->GetActorLocation());
		}
	}
}
