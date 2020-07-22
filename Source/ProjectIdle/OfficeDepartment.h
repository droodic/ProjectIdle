// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Department.h"
#include "InteractableObject.h"
#include "OfficeDepartment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API AOfficeDepartment : public ADepartment, public IInteractableObject
{
	GENERATED_BODY()
	
public:
	AOfficeDepartment();

	class UGameManager* GM;
	class AGameHUD* UI;
	class AFloorManager* ManagerRef;

	bool IsGenerating;

	UPROPERTY(BlueprintReadWrite) float TProgSalary = 0.f;
	UPROPERTY(BlueprintReadWrite) float TArtistSalary = 0.f;
	UPROPERTY(BlueprintReadWrite) float AvgProgMorale = 0.f;
	UPROPERTY(BlueprintReadWrite) float AvgArtistMorale = 0.f;

	//TArray<TSubclassOf<AItem*>> List;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<TSubclassOf<class AItem>> GameItemList;
	TArray<class Idea*> IdeaList;
	TArray<class Idea*> FinishedIdeaList;
	
	int Index = 0;
	UPROPERTY(BlueprintReadWrite) int ideasGenerated;

	UPROPERTY(BlueprintReadWrite) float AddedChance = 0;
	UPROPERTY(BlueprintReadWrite) float successChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrIdeaProgress = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxIdeaProgress = 100;

	UPROPERTY(EditAnywhere, Category = "Widgets") TArray<TSubclassOf<UUserWidget>> UserWidgets;

	UPROPERTY() class UCeoDepMenuWidget* OfficeDepMenuWidget; 
	UPROPERTY() class UIdeaBacklogWidget* BacklogWidget;
	UPROPERTY() class UShopWidget* ShopWidget;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ComputerMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ChairMesh;

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<class AActor>> SpawnActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	TArray<class AItem*> InventoryList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool StartingOffice;

	UPROPERTY(EditAnywhere) class ACameraActor* SpawnItemCamera;
	UPROPERTY(EditAnywhere) class TSubclassOf<class APreviewItem> PreviewItemBP;

private:
	//bool bInRadius = false;
	bool bInSpawnCamera = false;

	class AActor* PlayersCamera;

//Functions
public:
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void GenerateIdea();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void ViewBacklog();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void ViewShop();
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void CallMeeting();
	//UFUNCTION(BlueprintCallable, Category = "CPP Functions") void HireEmployee(TArray<TSubclassOf<AEmployee>> SpawnEmployee, int Position);
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void PublishGame();
	//For future use, will spawn any actor
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") AActor* GenerateSavedActor(UClass* ClassRef);
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") AActor* GenerateSavedDecoration(UClass* ClassRef);
	UFUNCTION(BlueprintCallable, Category = "CPP Functions") void GenerateActor(int Position, ERole EmpRole);
	UFUNCTION(BlueprintCallable) void GetDepartmentUIValues();
	void PopulateIdeaListFromSave(Idea* Idea);
	void SpawnItemInWorld(AItem* item);
	void EditPlacedItems();
	void Return();
	void BacklogReturn();
	void ShopReturn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::RightMouseButton) override;

	class Idea GenerateIdeaValues();

	// Inherited via IInteractableObject
	virtual void OnInteract();
};
