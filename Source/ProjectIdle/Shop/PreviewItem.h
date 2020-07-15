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
	// Sets default values for this actor's properties
	APreviewItem();

	UStaticMeshComponent* MeshComponent;

	class AItem* ItemReference;

private:
	bool bIsOverlapping = false;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	void Tick(float DeltaTime) override;

};
