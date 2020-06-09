// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Department.h"
#include "OfficeDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AOfficeDepartment : public ADepartment
{
	GENERATED_BODY()
	
public:
	AOfficeDepartment();

	bool IsGenerating;

	class UGameManager* GM;
	class AGameHUD* UI;

	int Index = 0;

	UPROPERTY(BlueprintReadWrite) float TProgSalary = 0.f;
	UPROPERTY(BlueprintReadWrite) float TArtistSalary = 0.f;
	UPROPERTY(BlueprintReadWrite) float AvgProgMorale = 0.f;
	UPROPERTY(BlueprintReadWrite) float AvgArtistMorale = 0.f;

	TArray<class Idea*> IdeaList;
	TArray<class Idea*> FinishedIdeaList;
	
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxIdeaProgress = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets") TArray<TSubclassOf<UUserWidget>> UserWidgets;

	UPROPERTY() class UCeoDepMenuWidget* OfficeDepMenuWidget; //added in gamehud, get ref from gamehud instead
	UPROPERTY() class UIdeaBacklogWidget* BacklogWidget;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ComputerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ChairMesh;

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<class AEmployee>> SpawnWorker;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<class AActor>> SpawnActors;

	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

//Functions
public:
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void ViewBacklog();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void CallMeeting();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireEmployee(TArray<TSubclassOf<AEmployee>> SpawnEmployee, int Position);
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void PublishGame();
	//For future use, will spawn any actor
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void GenerateActor(TArray<TSubclassOf<AActor>> SpawnEmployee, int Position);
	//UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireProgrammer();
	//UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireArtist();

	void Back();
	UFUNCTION(BlueprintCallable) void GetDepartmentUIValues();
	//int GetArtistSalary();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	class Idea GenerateIdeaValues();
};
