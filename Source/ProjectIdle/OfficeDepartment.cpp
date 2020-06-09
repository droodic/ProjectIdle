// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "CeoDepMenuWidget.h"
#include "Employees/Programmer.h"
#include "Employees/Artist.h"
#include "Department.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "GameManager.h"
#include "GameHUD.h"
#include "Workstation.h"
#include "Engine/World.h"
#include "Widgets/IdeaButton.h" 
#include "Widgets/IdeaBacklogWidget.h" 
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

void AOfficeDepartment::BeginPlay()
{
	Super::BeginPlay();
	GM = GetWorld()->GetGameInstance<UGameManager>();
	GM->OfficeDepartment = this;
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
		//OfficeDepMenuWidget->AddToRoot();
	}

	//GetDepartmentUIValues(); //call this on click to see ui in wbp
}

void AOfficeDepartment::ViewBacklog()
{
	if (BacklogWidget != nullptr)
	{
		OfficeDepMenuWidget->RemoveFromViewport();
		BacklogWidget->AddToViewport();
	}
}

void AOfficeDepartment::Back()
{
	if (BacklogWidget != nullptr)
	{
		BacklogWidget->RemoveFromViewport();
		OfficeDepMenuWidget->AddToViewport();
	}
}

void AOfficeDepartment::GetDepartmentUIValues()
{
	TProgSalary = 0.f;
	TArtistSalary = 0.f;
	AvgProgMorale = 0.f;
	AvgArtistMorale = 0.f;

	for (auto Employee : GM->EmployeeList) {
		if (Cast<AProgrammer>(Employee) != nullptr) {
			TProgSalary += Employee->Salary;
			AvgProgMorale += Employee->Morale;
		}
		else if (Cast<AArtist>(Employee) != nullptr) {
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
	GM->Money += UKismetMathLibrary::RandomIntegerInRange(15000, 25000); //Use algo later, and do real way of assgning money
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
			auto newIdea = new Idea("GAME " + FString::FromInt(randomNumber), "Game description of game " + FString::FromInt(randomNumber), Idea::GetRandomGenre(), FLinearColor::MakeRandomColor(), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(75.f, 150.f), UKismetMathLibrary::RandomFloatInRange(75.f, 150.f));

			IdeaList.Insert(newIdea, Index);
			BacklogWidget->DisplayNewIdea(IdeaList[Index]);
			
			Index++;
		}
	}
}

void AOfficeDepartment::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		if (OfficeDepMenuWidget != nullptr) //&& OfficeDepMenuWidget->IsValidLowLevel())
		{
			OfficeDepMenuWidget->AddToViewport();
		}

		//UI->ShowWidget(OfficeDepMenuWidget, UserWidgets[1]); 
	}
}

void AOfficeDepartment::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (Cast<AProjectIdleCharacter>(OtherActor) != nullptr)
	{
		if (OfficeDepMenuWidget->IsInViewport())
		{
			OfficeDepMenuWidget->RemoveFromViewport();
		}
		else if (BacklogWidget->IsInViewport())
		{
			BacklogWidget->RemoveFromViewport();
		}
	}
}

void AOfficeDepartment::HireEmployee(TArray<TSubclassOf<AEmployee>> SpawnEmployee, int Position)
{
	if (SpawnEmployee[Position])
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = GetInstigator();

			FVector SpawnLocation = FVector(0, 0, 270);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			World->SpawnActor<AEmployee>(SpawnEmployee[Position], SpawnLocation, SpawnRotation, SpawnParameters);

		}
	}
}

//Future transition 
void AOfficeDepartment::GenerateActor(TArray<TSubclassOf<AActor>> Spawn, int Position)
{

	if (Spawn[Position])
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FVector SpawnLocation;
			FRotator SpawnRotation;
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = GetInstigator();
			if (Position == 0 || Position == 1)
			{
				SpawnLocation = GM->Door->GetActorLocation();
				SpawnRotation = FRotator::ZeroRotator;
			}
			if (Position == 3)
			{
				FVector OffSet = FVector(0, -320, 0);
				int lastPosition = GM->WorkstationList.Num() - 1;
				SpawnLocation = GM->WorkstationList[lastPosition]->GetActorLocation() - OffSet;
				SpawnRotation = FRotator::ZeroRotator;
			}

			World->SpawnActor<AActor>(Spawn[Position], SpawnLocation, SpawnRotation, SpawnParameters);
			GetDepartmentUIValues();
		}
	}
}
