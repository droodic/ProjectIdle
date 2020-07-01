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

UENUM(Meta = (ScriptName = "SubCategory"))
enum class ESubCategory : uint8
{
	Monitor            UMETA(DisplayName = "Monitor"),
	Keyboard		   UMETA(DisplayName = "Keyboard"),
	Desk			   UMETA(DisplayName = "Desk"),
	Chair			   UMETA(DisplayName = "Chair"),
	FloorMat		   UMETA(DisplayName = "Floor"),
	WallMat			   UMETA(DisplayName = "Wall"),
	Other			   UMETA(DisplayName = "Other")
};

UCLASS()
class PROJECTIDLE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditDefaultsOnly) class UMaterial* Material;

	UPROPERTY(EditAnywhere) int ItemCompileRate; //If Monitor for now yolo
	UPROPERTY(EditDefaultsOnly) int ItemID;
	UPROPERTY(EditDefaultsOnly) int ItemPrice;
	int ItemCount = 0;
	
	UPROPERTY(EditDefaultsOnly) FString ItemName;
	UPROPERTY(EditDefaultsOnly) FString ItemDescription;

	UPROPERTY(EditDefaultsOnly) ECategory ItemCategory;
	UPROPERTY(EditDefaultsOnly) ESubCategory ItemSubCategory;

	UPROPERTY(EditDefaultsOnly) class UTexture2D* ItemImage;

	class UItemButton* ItemButton;
};
