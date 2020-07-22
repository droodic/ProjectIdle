// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewItem.h"
#include "Item.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/CeoDepMenuWidget.h"
#include "ProjectIdle/Widgets/InventoryButton.h"

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

	GameManager = GetWorld()->GetGameInstance<UGameManager>();
	OfficeDepartmentWidget = GameManager->OfficeDepartment->OfficeDepMenuWidget;
}

void APreviewItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bOnce)
	{
		bOnce = true;
		if (ItemReference != nullptr)
		{
			MeshComponent->SetStaticMesh(ItemReference->ItemMesh->GetStaticMesh());
			MeshComponent->SetRelativeScale3D(ItemReference->ItemMesh->GetRelativeScale3D());

			for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
			{
				if (OverlappingMaterial != nullptr && MeshComponent->GetMaterial(i) != nullptr)
				{
					MeshComponent->SetMaterial(i, PreviewMaterial);
				}
			}
		}
	}

	FHitResult hitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

	MeshComponent->SetWorldLocation(hitResult.Location);

	if (!bIsOverlapping)
	{
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			if (ItemReference != nullptr)
			{
				GetWorld()->SpawnActor<AItem>(ItemReference->ItemBP, hitResult.Location, MeshComponent->GetRelativeRotation());
				
				for (int i = 0; i < OfficeDepartmentWidget->OfficeDecoration_WB->GetChildrenCount(); i++)
				{
					auto inventoryButton = Cast<UInventoryButton>(OfficeDepartmentWidget->OfficeDecoration_WB->GetChildAt(i));

					if (ItemReference->ItemID == inventoryButton->Item->ItemID)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::FromInt(inventoryButton->Item->ItemCount));

						if (inventoryButton->Item->ItemCount > 1)
						{
							inventoryButton->Item->ItemCount--;
							inventoryButton->ItemCount_T->SetText(FText::FromString(FString::FromInt(inventoryButton->Item->ItemCount)));
						}
						else
						{
							OfficeDepartmentWidget->OfficeDecoration_WB->RemoveChildAt(i);
						}
					}
				}
			}

			Destroy();
		}
	}

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::MouseScrollUp))
	{
		MeshComponent->AddLocalRotation(FRotator(0.f, -RotationRate, 0.f));
	}
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::MouseScrollDown))
	{
		MeshComponent->AddLocalRotation(FRotator(0.f, RotationRate, 0.f));
	}

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		GameManager->InEditMode = false;
		Destroy();
	}
}

void APreviewItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	bIsOverlapping = true;

	for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
	{
		if (OverlappingMaterial != nullptr && MeshComponent->GetMaterial(i) != nullptr)
		{
			MeshComponent->SetMaterial(i, OverlappingMaterial);
		}
	}
}

void APreviewItem::NotifyActorEndOverlap(AActor* OtherActor)
{
	bIsOverlapping = false;

	for (int i = 0; i < MeshComponent->GetNumMaterials(); i++)
	{
		if (OverlappingMaterial != nullptr && MeshComponent->GetMaterial(i) != nullptr)
		{
			MeshComponent->SetMaterial(i, PreviewMaterial);
		}
	}
}
