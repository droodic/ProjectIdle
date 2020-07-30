// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "GameSave.h"
#include "Idea.h"
#include "OfficeDepartment.h"
#include "Employees/FloorManager.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "MeetingDepartment.h"



UGameManager::UGameManager() {
	Money = 180000; //temp
}

void UGameManager::Init()
{

}

void UGameManager::PopulateSaveFiles() {
	FString dir = FPaths::ProjectSavedDir();
	FString fileExt = TEXT("sav");

	IFileManager::Get().FindFiles(SaveFileNames, *dir, *fileExt);
}

void UGameManager::SaveGame(FString SaveFile)
{
	//Old approach
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	SaveGameInstance->Saved_Money = Money;
	SaveGameInstance->InventoryList.Empty();

	TArray<AItem*> inventoryList;
	InventoryList.GenerateKeyArray(inventoryList);

	for (auto Item : inventoryList) {
		SaveGameInstance->InventoryList.Add(Item);
	}
	for (auto Idea : OfficeDepartment->IdeaList) {
		SaveGameInstance->IdeaList.Add(Idea);
	}
	SaveGameInstance->SavedTime = FDateTime::Now();

	//Save Company Rating / Level
	SaveGameInstance->CompanyLevel = CompanyLevel;
	SaveGameInstance->CurrentExp = CurrentExp;
	SaveGameInstance->MaxExp = MaxExp;

	//Save Floor Material
	SaveGameInstance->FloorMaterialID = FloorMaterialID;
	SaveGameInstance->IsFloorUpgraded = IsFloorUpgraded;
	SaveGameInstance->WallMaterialID = WallMaterialID;

	if (OfficeDepartment->ManagerRef != nullptr) {
		SaveGameInstance->NumEmployees = EmployeeList.Num();
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Saving manager");
		SaveGameInstance->AutoManaging = OfficeDepartment->ManagerRef->AutoManaging;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "numemployeee saved: " + FString::FromInt(SaveGameInstance->NumEmployees));
	}

	//SaveGameInstance->IdeaInProduction = IdeaInProduction;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);

	checkSlow(World != nullptr);
	UWorld* World = GetWorld();
	FGameSavedData SaveGameData;
	FString outPath = FPaths::ProjectSavedDir() + SaveFile;//SaveGameData.Timestamp.ToString() + TEXT(".sav")

	SaveGameData.Timestamp = FDateTime::Now();
	FString mapName = World->GetMapName();
	SaveGameData.MapName = *mapName;
	mapName.Split("UEDPIE_0_", nullptr, &mapName);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableActorInterface::StaticClass(), Actors);

	TArray<FActorSavedData> SavedActors;
	for (auto Actor : Actors)
	{
		FActorSavedData ActorRecord;
		ActorRecord.MyName = FName(*Actor->GetName());
		ActorRecord.MyClass = Actor->GetClass()->GetPathName();
		ActorRecord.MyTransform = Actor->GetTransform();
		FMemoryWriter MemoryWriter(ActorRecord.MyData, true);
		FSaveGameArchive Ar(MemoryWriter);
		ISaveableActorInterface::Execute_ActorSaved(Actor);
		Actor->Serialize(Ar);

		SavedActors.Add(ActorRecord);
	}

	FBufferArchive SaveData;
	SaveGameData.SavedActors = SavedActors;
	SaveData << SaveGameData;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Savename : " + outPath);
	FFileHelper::SaveArrayToFile(SaveData, *outPath);
	SaveData.FlushCache();
	SaveData.Empty();
}

void UGameManager::LoadGame(FString SaveFile)
{
	//Old approach
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	SaveGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));
	Money = SaveGameInstance->Saved_Money;
	InventoryList.Empty();
	OfficeDepartment->IdeaList.Empty();

	for (auto Item : SaveGameInstance->InventoryList) {
		InventoryList.Add(Item);
		if (Item->ItemCategory == ECategory::Materials) {
			if (Item->ItemSubCategory == ESubCategory::Floor) {
				OfficeDepartment->OfficeDepMenuWidget->AddItemToInventory(Item);
				//OfficeDepartment->OfficeDepMenuWidget->FloorMaterial_HB->AddChild(Item.Default);
			}
			else if (Item->ItemSubCategory == ESubCategory::Wall) {
				OfficeDepartment->OfficeDepMenuWidget->WallMaterial_HB;
				OfficeDepartment->OfficeDepMenuWidget->AddItemToInventory(Item);

			}
		}

		for (auto Idea : SaveGameInstance->IdeaList) {
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Loading Idea");
			OfficeDepartment->IdeaList.Add(Idea);
			OfficeDepartment->PopulateIdeaListFromSave(Idea);
		}

		IsFloorUpgraded = SaveGameInstance->IsFloorUpgraded;
		if (IsFloorUpgraded) {
			OfficeDepartment->OfficeDepMenuWidget->CreateDepartment();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::FromInt(IsFloorUpgraded));

		CompanyLevel = SaveGameInstance->CompanyLevel;
		CurrentExp = SaveGameInstance->CurrentExp;
		MaxExp = SaveGameInstance->MaxExp;

		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Floor mat ID: " + FString::FromInt(SaveGameInstance->FloorMaterialID));
		for (auto Floor : OfficeDepartment->FloorMaterialList) {

			if (SaveGameInstance->FloorMaterialID == Floor.GetDefaultObject()->ItemID) {
				for (auto F : FloorList) {
					F->UpdateMaterial(Floor.GetDefaultObject());
				}
				//FloorList[i]->UpdateWallMaterial(Floor);
			}
			if (SaveGameInstance->WallMaterialID == Floor.GetDefaultObject()->ItemID) {
				for (auto W : WallList) {
					W->UpdateMaterial(Floor.GetDefaultObject());
				}
			}
		}


		//if (SaveGameInstance->AutoManaging == true) {
		FDateTime CurrentTime = FDateTime::Now();
		FTimespan Difference;
		Difference = CurrentTime - SaveGameInstance->SavedTime;

		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Time spent since last save:(seconds) " + FString::FromInt(Difference.GetTotalSeconds()));

		int IdeasToGenerate = Difference.GetTotalSeconds();
		if (IdeasToGenerate > 0) { //&& SaveGameInstance->NumEmployees > 0) {
			int Multiplier = 1; //SaveGameInstance->NumEmployees / 8;   numEmployees not loading, find out why
			IdeasToGenerate /= 3 * (Multiplier); // 3 minutes per idea generate
			OfficeDepartment->OfficeDepMenuWidget->ClearFinishedGames();

			OfficeDepartment->OfficeDepMenuWidget->T_TimePast->SetText(FText::AsTimespan(Difference));
			OfficeDepartment->OfficeDepMenuWidget->T_NumIdeas->SetText(FText::FromString(FString::FromInt(IdeasToGenerate)));
			OfficeDepartment->OfficeDepMenuWidget->LoadGameCanvas->SetVisibility(ESlateVisibility::Visible);

			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Loading Ideas generated since last save" + FString::FromInt(Difference.GetTotalSeconds()));
			for (int i = 0; i < IdeasToGenerate; i++) {
				//Generate Idea in Publish List
				auto randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 100);
				auto newIdea = new Idea("GAME " + FString::FromInt(randomNumber), "Game description of game " + FString::FromInt(randomNumber), Idea::GetRandomGenre(), FLinearColor::MakeRandomColor(), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(50.f, 150.f), UKismetMathLibrary::RandomFloatInRange(50.f, 150.f));
				if (OfficeDepartment->OfficeDepMenuWidget != nullptr) {

					OfficeDepartmentList[Character->CurrentFloor - 1]->OfficeDepMenuWidget->GetFinishedIdea(newIdea);
				}
			}
		}

		FString outPath = FPaths::ProjectSavedDir() + SaveFile;

		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Loading saveName : " + outPath);
		if (!FFileHelper::LoadFileToArray(BinaryData, *outPath))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "LOAD FAILED");
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(FString("Game Load Failed: ") + outPath));
			return;
		}


		checkSlow(World != nullptr);
		FMemoryReader FromBinary = FMemoryReader(BinaryData, true);
		FromBinary.Seek(0);

		FGameSavedData SaveGameData;
		FromBinary << SaveGameData;

		FromBinary.FlushCache();
		FromBinary.Close();

		//UMasteringGameInstance* gameInst = UMasteringGameInstance::GetInstance();
		//FVector playerSafeLoc = SaveGameData.PlayerSafeLocation;
		//gameInst->SetPlayerSafeLocation(playerSafeLoc);

		FString mapName = SaveGameData.MapName.ToString();
		FString currentMapName = GetWorld()->GetMapName();
		currentMapName.Split("UEDPIE_0_", nullptr, &currentMapName);

		OnGameLoadedFixup(GetWorld());
		//if (mapName == currentMapName)
		//{
		//	//GetWorld()->ServerTravel("?Restart", true);
		//	UGameplayStatics::OpenLevel(GetWorld(), *mapName);
		//}
		//else
		//{
		//	UGameplayStatics::OpenLevel(GetWorld(), *mapName);
		//}

		//UGameplayStatics:
		//UGameplayStatics::OpenLevel(GetWorld(), "TopDownExampleMap");
	}
}

void UGameManager::OnGameLoadedFixup(UWorld* World) {

	if (BinaryData.Num() == 0)
	{
		checkSlow(World->GetFirstPlayerController() != nullptr);
		return;
	}

	FMemoryReader FromBinary = FMemoryReader(BinaryData, true);
	FromBinary.Seek(0);

	FGameSavedData SaveGameData;
	FromBinary << SaveGameData;

	FromBinary.FlushCache();
	FromBinary.Close();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(World, USaveableActorInterface::StaticClass(), Actors);

	TArray<FActorSavedData> ActorDatas = SaveGameData.SavedActors;

	// iterate these arrays backwards as we will remove objects as we go, can also use iterators, but RemoveAt is simpler here for now
	for (int i = Actors.Num() - 1; i >= 0; --i)
	{
		AActor* Actor = Actors[i];

		for (int j = ActorDatas.Num() - 1; j >= 0; --j)
		{
			FActorSavedData ActorRecord = ActorDatas[j];

			// These are actors spawned into the world that we also found in our save data (TODO: use TArray intersection?)
			if (ActorRecord.MyName == *Actor->GetName())
			{
				FMemoryReader MemoryReader(ActorRecord.MyData, true);
				FSaveGameArchive Ar(MemoryReader);

				Actor->Serialize(Ar);
				Actor->SetActorTransform(ActorRecord.MyTransform);
				ISaveableActorInterface::Execute_ActorLoaded(Actor);

				APawn* pawn = Cast<APawn>(Actor);
				if (pawn != nullptr)
				{
					// controller needs the rotation too as this may set the pawn's rotation once play starts
					AController* controller = pawn->GetController();
					controller->ClientSetRotation(ActorRecord.MyTransform.Rotator());
				}

				ActorDatas.RemoveAt(j);
				Actors.RemoveAt(i);
				break;
			}
		}
	}

	// These are actors in our save data, but not in the world, spawn them
	for (FActorSavedData ActorRecord : ActorDatas)
	{
		FVector SpawnPos = ActorRecord.MyTransform.GetLocation();
		FRotator SpawnRot = ActorRecord.MyTransform.Rotator();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Name = ActorRecord.MyName;

		FActorSpawnParameters SpawnParameters;

		// if we were in a space when saved, we should be able to spawn there again when loaded, but we could also
		// be overlapping an object that loaded, but will be subsequently destroyed below as it was there at level start
		// but not there at save time
		UClass* SpawnClass = FindObject<UClass>(ANY_PACKAGE, *ActorRecord.MyClass);
		FVector SpawnLocation;
		FRotator SpawnRotation;
		if (SpawnClass) //&& Cast<AEmployee>(SpawnClass))
		{
			//OfficeDepartment->GenerateActor(0, ERole::Programmer);
			AActor* NewActor = OfficeDepartment->GenerateSavedActor(SpawnClass);//IFemployee, figure way to scale with other type actor like workstation?
			FMemoryReader MemoryReader(ActorRecord.MyData, true);
			FSaveGameArchive Ar(MemoryReader);

			if (NewActor != nullptr && Cast<AEmployee>(NewActor)) {
				NewActor->Serialize(Ar);
				NewActor->SetActorTransform(ActorRecord.MyTransform);
				ISaveableActorInterface::Execute_ActorLoaded(NewActor);
				if (Cast<AEmployee>(NewActor) != nullptr) {
					if (Cast<AEmployee>(NewActor)->Gendre == 0) {
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Cast<AEmployee>(NewActor)->Gendre));
						Cast<AEmployee>(NewActor)->GetMesh()->SetSkeletalMesh(OfficeDepartment->MaleEmployeeMeshList[Cast<AEmployee>(NewActor)->MeshID]);
					}
					else if (Cast<AEmployee>(NewActor)->Gendre == 1) {
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Cast<AEmployee>(NewActor)->Gendre));
						Cast<AEmployee>(NewActor)->GetMesh()->SetSkeletalMesh(OfficeDepartment->FemaleEmployeeMeshList[Cast<AEmployee>(NewActor)->MeshID]);
					}
				}
			}
			else if (NewActor != nullptr && Cast<AEmployee>(NewActor) == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "Spawning Decoration");
				NewActor->Serialize(Ar);
				NewActor->SetActorTransform(ActorRecord.MyTransform);
				ISaveableActorInterface::Execute_ActorLoaded(NewActor);
			}

			else if (NewActor == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Cannot Spawn Actor - Collision Problem");
			}
		}
	}

	// These are actors in the world that are not in our save data, destroy them (for example, a weapon pickup that was, well, picked up)
	for (auto Actor : Actors)
	{
		Actor->Destroy();
	}

	BinaryData.Empty();

	//postload function
	for (auto Station : WorkstationList) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Looping Stations, Station ID: " + FString::FromInt(Station->WorkstationIndex));

		if (Station->IsEnabled) {
			Station->EnableStation(true);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Enabling station " + FString::FromInt(Station->WorkstationIndex));

			//Set Meshes, move to function in Workstation when works? 
			Station->UpgradeMeshFromSave();

		}
	}


}