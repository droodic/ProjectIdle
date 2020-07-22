// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PreviewItem.generated.h"

UCLASS()
class PROJECTIDLE_API APreviewItem : public AActor
{
	GENERATED_BODY()
	
public:	
	APreviewItem();

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* MeshComponent;

	class AItem* ItemReference;

	UPROPERTY(EditDefaultsOnly) class UMaterial* PreviewMaterial;
	UPROPERTY(EditDefaultsOnly) class UMaterial* OverlappingMaterial;

	UPROPERTY(EditDefaultsOnly) float RotationRate = 10.f;

private:
	bool bIsOverlapping = false;
	bool bOnce = false;

	class UGameManager* GameManager;
	class AOfficeDepartment* OfficeDepartment;

protected:
	void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	void Tick(float DeltaTime) override;

};
