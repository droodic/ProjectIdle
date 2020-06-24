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


UCLASS()
class PROJECTIDLE_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

	class UGameManager* GM;

	UPROPERTY() USceneComponent* Root;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere) UMaterial* Material;
	UPROPERTY(EditAnywhere) UMaterial* UpgradeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsEnabled") bool IsEnabled;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ObjectType") ObjectType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsEnabled") bool RemovableWall;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void UpdateWallMaterial(UMaterialInterface* NewMaterial);
	UFUNCTION() void UpdateWallMaterialTest();
	UFUNCTION() void ActivateWallAndFloor();
	UFUNCTION() void DeactivateWallAndFloor();
	UFUNCTION() void EnableObject(bool Enabled);



};
