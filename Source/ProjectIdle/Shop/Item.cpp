// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "PreviewItem.h"
#include "ProjectIdle/GameManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = ItemMesh;

	AutoReceiveInput = EAutoReceiveInput::Player0;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	GameManager = GetWorld()->GetGameInstance<UGameManager>();
}

void AItem::NotifyActorOnClicked(FKey ButtonPressed)
{
	if (GameManager->InEditMode)
	{
		if (!GameManager->IsHoldingAPreview)
		{
			FHitResult hitResult;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

			if (PreviewItemBP != nullptr)
			{
				APreviewItem* previewItemReference = GetWorld()->SpawnActor<APreviewItem>(PreviewItemBP, hitResult.Location, ItemMesh->GetRelativeRotation());
				if (previewItemReference) {
					previewItemReference->ItemReference = this;
				}
				else {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "SPAWNFAILED -> PreviewItemBP is null");
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PreviewItemBP is null");
			}

			GameManager->IsHoldingAPreview = true;
			Destroy();
		}
	}
	else { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Not on edit Mode"); }
}
