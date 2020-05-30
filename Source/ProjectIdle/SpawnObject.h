// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Employees/Programmer.h"
#include "SpawnObject.generated.h"

UCLASS()
class PROJECTIDLE_API ASpawnObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnObject();

	//UPROPERTY(EditAnywhere) TSubclassOf<class AEmployee> SpawnProgrammer;
	//UPROPERTY(EditAnywhere) TSubclassOf<class AEmployee> SpawnArtist;
	//class UGameManager* GM;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireProgrammer();
	//UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireArtist();
	virtual void Tick(float DeltaTime) override;
};
