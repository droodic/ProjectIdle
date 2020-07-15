// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewItem.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APreviewItem::APreviewItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;
}

void APreviewItem::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = ItemReference->ItemMesh;
}

void APreviewItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

	MeshComponent->SetWorldLocation(hitResult.Location);

	if (!bIsOverlapping)
	{
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			GetWorld()->SpawnActor<AItem>(ItemReference->ItemBP, hitResult.Location, MeshComponent->GetRelativeRotation());
			Destroy();
		}
		else
		{
			Destroy();
		}
	}

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(EKeys::Right))
	{
		MeshComponent->AddLocalRotation(FRotator(0.f, 90.f, 0.f));
	}
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(EKeys::Left))
	{
		MeshComponent->AddLocalRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void APreviewItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	bIsOverlapping = true;
}

void APreviewItem::NotifyActorEndOverlap(AActor* OtherActor)
{
	bIsOverlapping = false;
}
