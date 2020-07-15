// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"



UCLASS()
class PROJECTIDLE_API AChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();

	class UGameManager* GM;

	UPROPERTY() FVector ChairLocation;
	UPROPERTY() USceneComponent* Root;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Mesh;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
