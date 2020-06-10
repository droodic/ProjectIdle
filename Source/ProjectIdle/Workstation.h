// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Workstation.generated.h"

enum class EType : int16
{
	PROGRAMMER,
	ARTIST
};


UCLASS()
class PROJECTIDLE_API AWorkstation : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AWorkstation();
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* DeskMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ComputerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ChairMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* KeyboardMesh;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UpgradeMonitor;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UpgradeKeyboard;
	//UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UpgradeChair;
	//UPROPERTY(VisibleAnywhere) TArray<UStaticMeshComponent*> MeshA;

	UPROPERTY()
	FVector StationLocation;

	UPROPERTY()
		FVector StationVector;

	UPROPERTY() bool HasEmployee;

	UPROPERTY() bool IsObjectDisable;
	UPROPERTY(EditAnywhere, Category = "Disable") bool DisableObject;

	//class UWorkstationUpgradeWidget* Upgrade;
	class UGameManager* GM;
	APlayerCameraManager* Camera;
    EType type;
	class AGameHUD* UI;

	UPROPERTY(EditAnywhere, Category = "Widgets") TSubclassOf<UUserWidget> UserWidget;

	UPROPERTY() class UWorkstationUpgradeWidget* UpgradeWidget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::RightMouseButton) override;

	UFUNCTION() void UpdateWorkstationPosition();
	UFUNCTION() void DisableStation(bool Disable);
	UFUNCTION() int WorkstationActiveLenght();
	UFUNCTION() void UpgradeMesh(int Index);
	//UFUNCTION() void TestFunction();
};
