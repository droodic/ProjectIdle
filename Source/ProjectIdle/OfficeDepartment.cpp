// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "Shop/Item.h"
#include "Shop/PreviewItem.h"
#include "CeoDepMenuWidget.h"
#include "Department.h"
#include "GameManager.h"
#include "Employees/FloorManager.h"
#include "GameHUD.h"
#include "Workstation.h"
#include "Engine/World.h"
#include "Employees/Employee.h"
#include "Employees/Artist.h"
#include "Employees/Programmer.h"
#include "Widgets/IdeaButton.h" 
#include "Widgets/ShopWidget.h" 
#include "Widgets/MoneyWidget.h" 
#include "Widgets/IdeaBacklogWidget.h" 
#include "Components/DecalComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectIdle/WorldObject/Door.h"

AOfficeDepartment::AOfficeDepartment()
{
	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComputerMesh"));
	ChairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChairMesh"));

	ComputerMesh->SetupAttachment(RootComponent);
	ChairMesh->SetupAttachment(RootComponent);
}

Idea AOfficeDepartment::GenerateIdeaValues()
{
	//Later find random name, description, etc
	return Idea(UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f));
}

void AOfficeDepartment::OnInteract()
{
	if (OfficeDepMenuWidget != nullptr)
	{
		if (!OfficeDepMenuWidget->IsInViewport() && !bInSpawnCamera)
		{
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->DisableMovement();
			OfficeDepMenuWidget->AddToViewport();

			if (GM->CurrentWidgetInDisplay != nullptr)
			{
				GM->CurrentWidgetInDisplay->RemoveFromViewport();
			}
		}
		else if (!bInSpawnCamera)
		{
			OfficeDepMenuWidget->RemoveFromViewport();
			UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}

void AOfficeDepartment::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->OfficeDepartment = this;
	if (StartingOffice)
	{
		GM->OfficeDepartmentList.Add(this);
	}
	else {
		GM->UnassignedOfficeDepartmentList.Add(this);
	}

	UI = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (UserWidgets[0] != nullptr)
	{
		BacklogWidget = CreateWidget<UIdeaBacklogWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidgets[0]);
		BacklogWidget->OfficeDepartment = this;
	}
	if (UserWidgets[1] != nullptr)
	{
		OfficeDepMenuWidget = CreateWidget<UCeoDepMenuWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidgets[1]);
		OfficeDepMenuWidget->OfficeDepartment = this;
	}
	if (UserWidgets[2] != nullptr)
	{
		ShopWidget = CreateWidget<UShopWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidgets[2]);
		ShopWidget->OfficeDepartment = this;
	}
	if (UserWidgets[3] != nullptr)
	{
		SpawnItemWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), UserWidgets[3]);
	}

	//GM->OnGameLoadedFixup(GetWorld());
	//GetDepartmentUIValues(); //call this on click to see ui in wbp
}

void AOfficeDepartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGenerating && CurrIdeaProgress <= MaxIdeaProgress)
	{
		CurrIdeaProgress += DeltaTime * 30; // + DeltaTime * SpeedModifer (? - Have some algorithm to be able to scale this)
		if (CurrIdeaProgress >= MaxIdeaProgress) {
			IsGenerating = false;
			CurrIdeaProgress = 0;
			ideasGenerated++;

			//auto newIdea = new Idea(GenerateIdeaValues());
			auto randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 100);
			auto newIdea = new Idea("GAME " + FString::FromInt(randomNumber), "Game description of game " + FString::FromInt(randomNumber), Idea::GetRandomGenre(), FLinearColor::MakeRandomColor(), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(50.f, 150.f), UKismetMathLibrary::RandomFloatInRange(50.f, 150.f));

			IdeaList.Insert(newIdea, Index);
			BacklogWidget->DisplayNewIdea(IdeaList[Index]);
			Index++;

			UI->MoneyWidget->ShowANotification("IDEA GENERATED!");

			if (ManagerRef != nullptr && ManagerRef->GeneratingIdea) {

				//ManagerRef->
				BacklogWidget->CallMeeting_M(ManagerRef);
				ManagerRef->GeneratingIdea = false;
				ManagerRef->IdeaIndex++; //use pop instead
			}
		}
	}

	if (bInSpawnCamera)
	{
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustPressed(EKeys::SpaceBar))
		{
			ReturnToOfficeDepartment();
		}
	}
}

#pragma region Backlog & Shop Widgets

void AOfficeDepartment::ViewBacklog()
{
	if (BacklogWidget != nullptr)
	{
		OfficeDepMenuWidget->RemoveFromViewport();
		BacklogWidget->AddToViewport();
	}
}

void AOfficeDepartment::ViewShop()
{
	if (ShopWidget != nullptr)
	{
		OfficeDepMenuWidget->RemoveFromViewport();
		ShopWidget->AddToViewport();
	}
}

void AOfficeDepartment::BacklogReturn()
{
	if (BacklogWidget != nullptr)
	{
		BacklogWidget->RemoveFromViewport();
		OfficeDepMenuWidget->AddToViewport();
	}
}

void AOfficeDepartment::ShopReturn()
{
	if (ShopWidget != nullptr)
	{
		ShopWidget->RemoveFromViewport();
		OfficeDepMenuWidget->AddToViewport();
	}
}

#pragma endregion

void AOfficeDepartment::Return()
{
	if (OfficeDepMenuWidget != nullptr)
	{
		OfficeDepMenuWidget->RemoveFromViewport();
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void AOfficeDepartment::GetDepartmentUIValues()
{
	TProgSalary = 0.f;
	TArtistSalary = 0.f;
	AvgProgMorale = 0.f;
	AvgArtistMorale = 0.f;

	for (auto Employee : GM->EmployeeList) {
		if (Employee->EmployeeRole == ERole::Programmer) {
			TProgSalary += Employee->Salary;
			AvgProgMorale += Employee->Morale;
		}
		else if (Employee->EmployeeRole == ERole::Artist) {
			TArtistSalary += Employee->Salary;
			AvgArtistMorale += Employee->Morale;
		}
	}

	AvgProgMorale = AvgProgMorale / GM->NumOfProgrammers;
	AvgArtistMorale = AvgArtistMorale / GM->NumOfArtists;
}


void AOfficeDepartment::GenerateIdea()
{
	IsGenerating = true;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Generating Idea");

	//When idea gen complete
	//Enable widget call meeting btn if >1?
}

void AOfficeDepartment::CallMeeting()
{
	/*
	for (AEmployee* emp : GM->EmployeeList) {
		emp->AI->GoMeeting();
	}
	move ai to meeting room, you meet them there to start progress
	*/
}

void AOfficeDepartment::PublishGame()
{
	FinishedIdeaList[OfficeDepMenuWidget->ChosenIndex]->IdeaButton->IsPublished = true;

	successChance = FinishedIdeaList[OfficeDepMenuWidget->ChosenIndex]->SuccessChance + AddedChance;
	float rateRolled = UKismetMathLibrary::RandomFloatInRange(0.f, 100.f);
	UI->MoneyWidget->ShowANotification(FString::FromInt(AddedChance) + " AddedChance");
	UI->MoneyWidget->ShowANotification(FString::FromInt(successChance) + " Chance");
	if (successChance >= rateRolled)
	{
		auto moneyGenerated = UKismetMathLibrary::RandomIntegerInRange(15000, 25000);
		if (GM->Money >= INT32_MAX || GM->Money + moneyGenerated > INT32_MAX)
		{
			UI->MoneyWidget->ShowANotification("MAX MONEY");
		}
		else
		{
			GM->Money += moneyGenerated;
			//GM->Money += UKismetMathLibrary::RandomIntegerInRange(15000, 25000); //Use algo later, and do real way of assgning money

			UI->MoneyWidget->ShowANotification("+ $" + FString::FromInt(moneyGenerated) + ".00", FLinearColor::Green);
		}

		FinishedIdeaList[OfficeDepMenuWidget->ChosenIndex]->IdeaButton->MoneyGenerated = moneyGenerated;
		OfficeDepMenuWidget->IdeaGeneratedMoney_T->SetText(FText::AsCurrency(moneyGenerated));
	}
	else
	{
		UI->MoneyWidget->ShowANotification("SORRY, THE GAME WAS NOT A SUCCESS", FLinearColor::Red);
		auto moneyGenerated = UKismetMathLibrary::RandomIntegerInRange(100, 1000);

		if (GM->Money >= INT32_MAX || GM->Money + moneyGenerated > INT32_MAX)
		{
			UI->MoneyWidget->ShowANotification("MAX MONEY");
		}
		else
		{
			GM->Money += moneyGenerated;
			UI->MoneyWidget->ShowANotification("+ $" + FString::FromInt(moneyGenerated) + ".00", FLinearColor::Green);
		}

		FinishedIdeaList[OfficeDepMenuWidget->ChosenIndex]->IdeaButton->MoneyGenerated = moneyGenerated;
		FinishedIdeaList[OfficeDepMenuWidget->ChosenIndex]->IdeaButton->PublishedColor = FLinearColor::Red;
		OfficeDepMenuWidget->IdeaGeneratedMoney_T->SetText(FText::AsCurrency(moneyGenerated));
	}
}

void AOfficeDepartment::NotifyActorOnClicked(FKey ButtonPressed)
{
	//if (bInRadius && OfficeDepMenuWidget != nullptr)
	//{
	//	if (!OfficeDepMenuWidget->IsInViewport())
	//	{
	//		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->DisableMovement();
	//		OfficeDepMenuWidget->AddToViewport();

	//		if (GM->CurrentWidgetInDisplay != nullptr)
	//		{
	//			GM->CurrentWidgetInDisplay->RemoveFromViewport();
	//		}
	//	}
	//	else
	//	{
	//		OfficeDepMenuWidget->RemoveFromViewport();
	//		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//	}
	//}

}

void AOfficeDepartment::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	//{
	//	bInRadius = true;
	//}
}

void AOfficeDepartment::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		//bInRadius = false;

		/*if (OfficeDepMenuWidget->IsInViewport())
		{
			OfficeDepMenuWidget->RemoveFromViewport();
		}
		else if (BacklogWidget->IsInViewport())
		{
			BacklogWidget->RemoveFromViewport();
		}
		else if (ShopWidget->IsInViewport())
		{
			ShopWidget->RemoveFromViewport();
		}*/
	}
}

void AOfficeDepartment::SpawnItemInWorld(AItem* item)
{
	bInSpawnCamera = true;

	OfficeDepMenuWidget->RemoveFromViewport();
	SpawnItemWidget->AddToViewport();

	PlayersCamera = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();

	if (SpawnItemCamera != nullptr)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(SpawnItemCamera);
	}

	FHitResult hitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);

	if (PreviewItemBP != nullptr)
	{
		APreviewItem* previewItemReference = GetWorld()->SpawnActor<APreviewItem>(PreviewItemBP, hitResult.Location, item->ItemMesh->GetRelativeRotation());
		previewItemReference->ItemReference = item;
	}
}

void AOfficeDepartment::EditPlacedItems()
{
	bInSpawnCamera = true;
	GM->InEditMode = true;

	OfficeDepMenuWidget->RemoveFromViewport();
	SpawnItemWidget->AddToViewport();

	PlayersCamera = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();

	if (SpawnItemCamera != nullptr)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(SpawnItemCamera);
	}
}

void AOfficeDepartment::ReturnToOfficeDepartment()
{
	bInSpawnCamera = false;
	GM->InEditMode = false;

	if (PlayersCamera != nullptr)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(PlayersCamera);
	}

	SpawnItemWidget->RemoveFromViewport();
	OfficeDepMenuWidget->AddToViewport();
}

void AOfficeDepartment::GetRandomMesh(AEmployee* EmployeeRef) {
	FRandomStream RStream;
	RStream.GenerateNewSeed();

	int RandomGendre = UKismetMathLibrary::RandomIntegerInRange(0, 1);
	if (RandomGendre == 0) {	//Male

		int Random = UKismetMathLibrary::RandomIntegerInRangeFromStream(0, GM->OfficeDepartment->MaleEmployeeMeshList.Num() - 1, RStream);

		while (PreviousMeshID == Random)
		{
			Random = UKismetMathLibrary::RandomIntegerInRangeFromStream(0, GM->OfficeDepartment->MaleEmployeeMeshList.Num() - 1, RStream);
		}

		EmployeeRef->GetMesh()->SetSkeletalMesh(GM->OfficeDepartment->MaleEmployeeMeshList[Random]);
		EmployeeRef->MeshID = Random;
		EmployeeRef->Gendre = 0;
		EmployeeRef->GetGendreName(0);
		PreviousMeshID = Random;
	}
	else if (RandomGendre == 1) {

		int Random = UKismetMathLibrary::RandomIntegerInRangeFromStream(0, GM->OfficeDepartment->FemaleEmployeeMeshList.Num() - 1, RStream);
		while (PreviousMeshID == Random)
		{
			Random = UKismetMathLibrary::RandomIntegerInRangeFromStream(0, GM->OfficeDepartment->FemaleEmployeeMeshList.Num() - 1, RStream);
		}

		EmployeeRef->GetMesh()->SetSkeletalMesh(GM->OfficeDepartment->FemaleEmployeeMeshList[Random]);
		EmployeeRef->MeshID = Random;
		EmployeeRef->Gendre = 1;
		EmployeeRef->GetGendreName(1);
		PreviousMeshID = Random;
	}
}

//Future transition 
void AOfficeDepartment::GenerateActor(int Position, ERole EmpRole)
{
	if (SpawnActors[Position])
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FVector SpawnLocation;
			FRotator SpawnRotation;
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = GetInstigator();
			if (Position == 0 || Position == 1 || Position == 2 || Position == 5)
			{
				int floor = GM->Character->CurrentFloor;
				SpawnLocation = GM->DoorList[floor - 1]->SpawnPoint->GetComponentLocation();
				SpawnRotation = FRotator::ZeroRotator;
				//SpawnRotation = GM->DoorList[floor - 1]->GetActorRotation();
			}

			if (Position == 4)
			{
				SpawnRotation = FRotator(0, -90, 0);
				SpawnLocation = FVector(510.0, -1520.0, 160.0); // Array of grid vector position later on
				AWorkstation* Station = World->SpawnActorDeferred<AWorkstation>(SpawnActors[Position], FTransform(SpawnRotation, SpawnLocation, FVector::OneVector), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				Station->WorkstationInit(EmpRole);
				Station->FinishSpawning(FTransform(SpawnRotation, SpawnLocation, FVector::OneVector));
				return;
			}

			auto Emp = World->SpawnActor<AEmployee>(SpawnActors[Position], SpawnLocation, SpawnRotation, SpawnParameters);
			Emp->EmployeeRole = EmpRole;
			//GM->TotalSalary += Emp->Salary;
			if (Cast<ASupervisor>(Emp) != nullptr) {
				Cast<ASupervisor>(Emp)->InitSupervisor(EmpRole); //quick workaround annoying beginplay pedantics of spawning
				Emp->AssignSupervisor();
			}
			GetRandomMesh(Emp);
			GetDepartmentUIValues();

		}
	}
}

/*AActor* AOfficeDepartment::GenerateSavedActor(UClass* ClassRef)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, "Spawning Saved Actor");

	UWorld* World = GetWorld();

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector NewVector = FVector(0, -50, 0);
	SpawnLocation = FVector(0, 0, 0); //GM->Door->GetActorLocation() + NewVector; 
	SpawnRotation = FRotator::ZeroRotator;

	auto Emp = World->SpawnActor<AEmployee>(ClassRef, SpawnLocation, SpawnRotation, SpawnParameters);
	if (Cast<ASupervisor>(Emp) != nullptr) {
		Cast<ASupervisor>(Emp)->InitSupervisor(Emp->EmployeeRole); //quick workaround annoying beginplay pedantics of spawning
		Emp->AssignSupervisor();
		GetDepartmentUIValues();
	}

	//GetRandomMesh(Emp)
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "Loading Emp");

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::FromInt(Emp->MeshID));
	Emp->GetMesh()->SetSkeletalMesh(EmployeeMeshList[Emp->MeshID]);

	GetDepartmentUIValues();
	return Emp;
}*/

AActor* AOfficeDepartment::GenerateSavedActor(UClass* ClassRef)
{
	UWorld* World = GetWorld();

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector NewVector = FVector(0, -50, 0);
	SpawnLocation = FVector(0, 0, 0); //GM->Door->GetActorLocation() + NewVector; 
	SpawnRotation = FRotator::ZeroRotator;

	auto ActorRef = GWorld->SpawnActor(ClassRef, &SpawnLocation, &SpawnRotation, SpawnParameters);
	if (Cast<ASupervisor>(ActorRef) != nullptr)
	{
		Cast<ASupervisor>(ActorRef)->InitSupervisor(Cast<ASupervisor>(ActorRef)->EmployeeRole); //quick workaround annoying beginplay pedantics of spawning
		Cast<ASupervisor>(ActorRef)->AssignSupervisor();
		GetDepartmentUIValues();
	}

	return ActorRef;
}

void AOfficeDepartment::PopulateIdeaListFromSave(Idea* Idea) {
	BacklogWidget->DisplayNewIdea(Idea);
}
