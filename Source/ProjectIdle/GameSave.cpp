// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSave.h"
#include "GameManager.h"
#include "Runtime\Engine\Classes\Engine\World.h"

UGameSave::UGameSave() {
	Saved_PlayerLocation = FVector(0, 0, 0);
}

void UGameSave::ClearLists() {
	InventoryList.Empty();
	WorkstationList.Empty();
}

//Method 1
//void UGameSave::SaveEmployeeRecords(FArchive Ar) {
//	// make hero records, grab all the heroes' class and name and put them in the struct
//	GM = GetWorld()->GetGameInstance<UGameManager>();
//	if (GM) {
//		TArray<FSaveGameActorData> EmployeeRecords;
//		if (Ar.IsSaving())
//		{
//			// Only do this when saving!
//			EmployeeRecords.AddDefaulted(GM->EmployeeList.Num());
//			for (int32 i = 0; i < GM->EmployeeList.Num(); ++i)
//			{
//				EmployeeRecords[i].EmployeeClass = GM->EmployeeList[i]->GetClass();
//				EmployeeRecords[i].EmployeeName = GM->EmployeeList[i]->GetName();
//			}
//		}
//		// save/load the struct!
//		Ar << EmployeeRecords;
//		TArray<AEmployee*> Employees;
//		if (Ar.IsLoading())
//		{
//			// When loading, just go through the records and respawn every unit
//			for (int32 i = 0; i < EmployeeRecords.Num(); ++i)
//			{
//				FActorSpawnParameters p;
//				p.Name = *EmployeeRecords[i].EmployeeName;
//				p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//				p.bNoFail = true;
//				//p.Owner = GameTeam;
//				AEmployee* Employee = GetWorld()->SpawnActor<AEmployee>(EmployeeRecords[i].EmployeeClass, p);
//				GM->EmployeeList.Add(Employee);
//				//PlayerState->Heroes.Add(Unit);
//			}
//		}
//		// During loading, at this point, your unit's properties (HP, mana, etc.) will be at default, so the below serialize code will "override" them to the saved values
//		// Save/load unit's properties
//		for (int32 i = 0; i < GM->EmployeeList.Num(); ++i)
//		{
//			Ar << GM->EmployeeList[i]->EmployeeRole;
//			Ar << GM->EmployeeList[i]->Position;
//			//Ar << GM->EmployeeList[i]->EmployeeName; Above name approach replace by thjis ?
//			Ar << GM->EmployeeList[i]->Morale;
//			Ar << GM->EmployeeList[i]->Performance;
//			Ar << GM->EmployeeList[i]->Salary;
//		}
//	}
//}
