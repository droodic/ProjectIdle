// Fill out your copyright notice in the Description page of Project Settings.


#include "Department.h"

// Sets default values
ADepartment::ADepartment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickableMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ADepartment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADepartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADepartment::NotifyHit(UPrimitiveComponent * MyComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector Hitlocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Super::NotifyHit(MyComp, OtherActor, OtherComp, bSelfMoved, Hitlocation, HitNormal, NormalImpulse, Hit);
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Player hit department"));
		//Show Department menu here
	}
}

