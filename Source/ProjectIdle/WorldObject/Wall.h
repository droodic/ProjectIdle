// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"



UENUM(Meta = (ScriptName = "ObjectType"))
enum class ObjectType : uint8
{
	Wall             UMETA(DisplayName = "Wall"),
	Floor		     UMETA(DisplayName = "Floor"),

};

UENUM(Meta = (ScriptName = "FloorType"))
enum class FloorType : uint8
{
	None     		UMETA(DisplayName = "None"),
	Dev             UMETA(DisplayName = "Dev"),
	Marketing		UMETA(DisplayName = "Marketing"),

};

UENUM(Meta = (ScriptName = "WallPosition"))
enum class WallPosition : uint8
{
	None             UMETA(DisplayName = "None"),
	Right            UMETA(DisplayName = "Right"),
	Left		     UMETA(DisplayName = "Left"),

};


UCLASS()
class PROJECTIDLE_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

	class UGameManager* GM;

	//UPROPERTY(SaveGame, BlueprintReadWrite) int FloorMatID = 0;

	UPROPERTY() USceneComponent* Root;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Mesh;
	UPROPERTY( EditAnywhere) UMaterial* Material;
	UPROPERTY( EditAnywhere) UMaterial* UpgradeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsEnabled") bool IsEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsEnabled") bool RemovableWall;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "ObjectType") ObjectType Type;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "FloorType") FloorType Flooring;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "WallPosition") WallPosition WallDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool StartingFloor;

	//int FloorLevel;
	bool IsFloorAssigned = false;
	FVector LeftSide;
	FVector RightSide;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) int FloorArtistCount = 0;
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite) int FloorProgrammerCount = 0;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void UpdateWallMaterial(AItem* FloorItem);
	UFUNCTION() void UpdateWallMaterialTest();
	UFUNCTION() void ActivateWallAndFloor();
	UFUNCTION() void DeactivateWallAndFloor();
	UFUNCTION() void EnableObject(bool Enabled);
	UFUNCTION() void AssignFloorLevel();


};
