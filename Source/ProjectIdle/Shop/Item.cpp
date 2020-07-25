// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "PreviewItem.h"
#include "ProjectIdle/GameManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	GameManager = GetWorld()->GetGameInstance<UGameManager>();
}

void AItem::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (GameManager->InEditMode)
	{
		FHitResult hitResult;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

		if (PreviewItemBP != nullptr)
		{
			APreviewItem* previewItemReference = GetWorld()->SpawnActor<APreviewItem>(PreviewItemBP, hitResult.Location, ItemMesh->GetRelativeRotation());
			previewItemReference->ItemReference = this;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PreviewItemBP is null");
		}

		Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Not on edit Mode");
	}
}