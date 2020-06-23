// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "GameSave.h"
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

void UGameManager::SaveGame()
{
	//Old approach
	//UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	//SaveGameInstance->Saved_Money = Money;
	//UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);

	FGameSavedData SaveGameData;
	SaveGameData.Timestamp = FDateTime::Now();
	UWorld* World = GetWorld();
	checkSlow(World != nullptr);

	//FString mapName = World->GetMapName();
	//mapName.Split("_", nullptr, &mapName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	//SaveGameData.MapName = *mapName;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableActorInterface::StaticClass(), Actors);

	TArray<FActorSavedData> SavedActors;
	for (auto Actor : Actors)
	{
		FActorSavedData ActorRecord;
		ActorRecord.MyName = FName(*Actor->GetName());
		ActorRecord.MyClass = Actor->GetClass()->GetPathName();
		ActorRecord.MyTransform = Actor->GetTransform();
		//ActorRecord.MyVelocity = Actor->GetVelocity();

		FMemoryWriter MemoryWriter(ActorRecord.MyData, true);
		FSaveGameArchive Ar(MemoryWriter);
		//AMasteringCharacter* Mast = Cast<AMasteringCharacter>(Actor);

		Actor->Serialize(Ar);

		//if (Mast != nullptr)
		//{
		//	UMasteringInventory* Inv = Mast->GetInventory();
		//	SaveGameData.InventoryData.CurrentWeapon = Inv->GetCurrentWeapon()->GetPathName();
		//	SaveGameData.InventoryData.CurrentWeaponPower = Inv->GetCurrentWeaponPower();
		//	for (FWeaponProperties weapon : Inv->GetWeaponsArray())
		//	{
		//		FInventoryItemData data;
		//		data.WeaponClass = weapon.WeaponClass->GetPathName();
		//		data.WeaponPower = weapon.WeaponPower;
		//		data.Ammo = weapon.Ammo;
		//		data.TextureClass = weapon.InventoryIcon->GetPathName();

		//		SaveGameData.InventoryData.WeaponsArray.Add(data);
		//	}
		//}

		SavedActors.Add(ActorRecord);
	}

	FBufferArchive SaveData;
	SaveGameData.SavedActors = SavedActors;
	SaveData << SaveGameData;
	FString outPath = FPaths::ProjectSavedDir() + "_Default"; //SaveGameData.Timestamp.ToString() + TEXT(".sav")
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Savename : " + outPath);
	FFileHelper::SaveArrayToFile(SaveData, *outPath);
	SaveData.FlushCache();
	SaveData.Empty();

	//APlayerController* playerController = World->GetFirstPlayerController();
	//if (playerController)
	//{
	//	playerController->bShowMouseCursor = false;
	//	FInputModeGameOnly InputMode;
	//	playerController->SetInputMode(InputMode);
	//	UGameplayStatics::SetGamePaused(this, false);
	//}

	//Close();



}

void UGameManager::LoadGame(FString SaveFile)
{
	//Old approach
	//UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	//SaveGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));
	//Money = SaveGameInstance->Saved_Money;
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

	//FString mapName = SaveGameData.MapName.ToString();

	//FString currentMapName = World->GetMapName();

	//currentMapName.Split("UEDPIE_0_", nullptr, &currentMapName);

	//if (mapName == currentMapName)
	//{
	//	World->ServerTravel("?Restart", true);
	//}
	//if(M)

	//UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetMapName());
	//GetWorld()->ServerTravel("?Restart", true);
	OnGameLoadedFixup(GetWorld());
}

void UGameManager::OnGameLoadedFixup(UWorld* World) {

	if (BinaryData.Num() == 0)
	{
		checkSlow(World->GetFirstPlayerController() != nullptr);
	//		FixupPlayer(World, charPawn);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "NOT SPAWNING ");
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

	//AMasteringCharacter* Char = nullptr; // if ever more than one, we'll need an array and a map to their inventory

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

				//AMasteringCharacter* Mast = Cast<AMasteringCharacter>(Actor);
				//if (Mast != nullptr)
				//{
				//	Char = Mast;
				//}

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

	//FixupPlayer(World, Char);

	// These are actors in our save data, but not in the world, spawn them
	for (FActorSavedData ActorRecord : ActorDatas)
	{
		FVector SpawnPos = ActorRecord.MyTransform.GetLocation();
		FRotator SpawnRot = ActorRecord.MyTransform.Rotator();
		FActorSpawnParameters SpawnParams;
		// if we were in a space when saved, we should be able to spawn there again when loaded, but we could also
		// be overlapping an object that loaded, but will be subsequently destroyed below as it was there at level start
		// but not there at save time
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Name = ActorRecord.MyName;
		UClass* SpawnClass = FindObject<UClass>(ANY_PACKAGE, *ActorRecord.MyClass);
		if (SpawnClass)
		{
			AActor* NewActor = GWorld->SpawnActor(SpawnClass, &SpawnPos, &SpawnRot, SpawnParams);
			FMemoryReader MemoryReader(ActorRecord.MyData, true);
			FSaveGameArchive Ar(MemoryReader);
			NewActor->Serialize(Ar);
			NewActor->SetActorTransform(ActorRecord.MyTransform);
			ISaveableActorInterface::Execute_ActorLoaded(NewActor);
		}
	}

	// These are actors in the world that are not in our save data, destroy them (for example, a weapon pickup that was, well, picked up)
	for (auto Actor : Actors)
	{
		Actor->Destroy();
	}

	BinaryData.Empty();
}