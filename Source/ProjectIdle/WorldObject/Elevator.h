// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectIdle/InteractableObject.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class PROJECTIDLE_API AElevator : public AActor, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

	UPROPERTY(VisibleAnywhere) UBoxComponent* CollisionBox;

	class AGameHUD* UI;
	class UGameManager* GM;
	UPROPERTY() FVector ElevatorLocation;
	UPROPERTY() USceneComponent* Root;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* ElevatorMesh;
	UPROPERTY(VisibleAnywhere) USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool StartingElevator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;

	UPROPERTY(EditAnywhere, Category = "Widgets")TSubclassOf<UUserWidget> UserWidget;
	UPROPERTY() class UElevatorWidget* ElevatorWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void OnInteract();
	
};
