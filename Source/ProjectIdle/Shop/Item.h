// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(Meta = (ScriptName = "Category"))
enum class ECategory : uint8
{
	ComputerComponents             UMETA(DisplayName = "Computer Components"),
	DeskAndChairs				   UMETA(DisplayName = "Desk & Chairs"),
	OfficeDecorations			   UMETA(DisplayName = "Office Decorations"),
	Materials					   UMETA(DisplayName = "Materials")
};

UCLASS()
class PROJECTIDLE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditDefaultsOnly) class UMaterial* Material;

	UPROPERTY(EditDefaultsOnly) int ItemID;
	UPROPERTY(EditDefaultsOnly) int ItemPrice;
	
	UPROPERTY(EditDefaultsOnly) FString ItemName;

	UPROPERTY(EditDefaultsOnly) ECategory ItemCategory;

	UPROPERTY(EditDefaultsOnly) class UTexture2D* ItemImage;

};
