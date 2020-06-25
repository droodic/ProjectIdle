// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "GameSave.h"
#include "OfficeDepartment.h"
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
	//SaveGameInstance->ClearLists();
	for (auto Item : InventoryList) {
		SaveGameInstance->InventoryList.Add(Item);
	}
	for (auto Station : WorkstationList) {
		if (Station->IsEnabled) {
			FSaveMesh SavedMesh;
			SavedMesh.WorkstationIndex = Station->WorkstationIndex;
			SavedMesh.S_ComputerMeshID = Station->ComputerMeshID;
			//SavedMesh.S_ComputerMesh->SetStaticMesh(Station->ComputerMesh->GetStaticMesh());
			SaveGameInstance->WorkstationMeshList.Add(SavedMesh);
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Station Saved, id: " + FString::FromInt(SavedMesh.S_ComputerMeshID));
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Station Saved, id: " + FString::FromInt(SavedMesh.WorkstationIndex));
			SaveGameInstance->WorkstationList.Add(Station);
			
		}
	}


	//SaveGameInstance->Saved_PlayerLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);

	checkSlow(World != nullptr);
	UWorld* World = GetWorld();
	FGameSavedData SaveGameData;
	FString outPath = FPaths::ProjectSavedDir() + SaveFile;//SaveGameData.Timestamp.ToString() + TEXT(".sav")

	SaveGameData.Timestamp = FDateTime::Now();
	FString mapName = World->GetMapName();
	SaveGameData.MapName = *mapName;
	mapName.Split("UEDPIE_0_", nullptr, &mapName);


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
		ISaveableActorInterface::Execute_ActorSaved(Actor);
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
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	SaveGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot("Default", 0));
	Money = SaveGameInstance->Saved_Money;
	InventoryList.Empty();
	WorkstationList.Empty();
	for (auto Item : SaveGameInstance->InventoryList) {
		InventoryList.Add(Item);
	}
	for (auto Station : SaveGameInstance->WorkstationList) {
		WorkstationList.Add(Station);
		Station->EnableStation(true);
		Station->HasEmployee = false;

		//Station->ComputerMesh->SetStaticMesh(Station->WorkstationSaveMesh[0]->GetStaticMesh());
	}
	for (auto SavedStation : SaveGameInstance->WorkstationMeshList) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "SavedStation ComputerID" + FString::FromInt(SavedStation.S_ComputerMeshID));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "SavedStation WorkstationID" + FString::FromInt(SavedStation.WorkstationIndex));
		//if (Station->WorkstationIndex == SavedStation.WorkstationIndex) {
		//	//function here to change mesh respectively to id given
		//	Station->UpgradeMeshFromSave(SavedStation);
		//	//Station->ComputerMeshID = SavedStation.S_ComputerMeshID;
		//}
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

void UGameManager::OnGameLoadedFixup(UWorld* World) {

	if (BinaryData.Num() == 0)
	{
		checkSlow(World->GetFirstPlayerController() != nullptr);
		//		FixupPlayer(World, charPawn);
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
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Name = ActorRecord.MyName;

		FActorSpawnParameters SpawnParameters;

		// if we were in a space when saved, we should be able to spawn there again when loaded, but we could also
		// be overlapping an object that loaded, but will be subsequently destroyed below as it was there at level start
		// but not there at save time
		UClass* SpawnClass = FindObject<UClass>(ANY_PACKAGE, *ActorRecord.MyClass);
		if (SpawnClass)
		{

			FVector SpawnLocation;
			FRotator SpawnRotation;



			//OfficeDepartment->GenerateActor(0, ERole::Programmer);
			AActor* NewActor = OfficeDepartment->GenerateSavedActor(SpawnClass);//IFemployee, figure way to scale with other type actor like workstation?
			FMemoryReader MemoryReader(ActorRecord.MyData, true);
			FSaveGameArchive Ar(MemoryReader);
			
			if (NewActor != nullptr) {
				NewActor->Serialize(Ar);
				NewActor->SetActorTransform(ActorRecord.MyTransform);
				ISaveableActorInterface::Execute_ActorLoaded(NewActor);
			}
			else {
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
}