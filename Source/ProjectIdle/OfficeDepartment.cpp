// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "Widgets/IdeaBacklogWidget.h" 
#include "CeoDepMenuWidget.h"
#include "Components/WidgetComponent.h"
#include "GameManager.h"
#include "GameHUD.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AOfficeDepartment::AOfficeDepartment() {
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
	GM = GetWorld()->GetGameInstance<UGameManager>(); //unused
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

			auto randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 100);
			//auto newIdea = new Idea(GenerateIdeaValues());
			auto newIdea = new Idea("GAME " + FString::FromInt(randomNumber), "Game description of game " + FString::FromInt(randomNumber), Idea::GetRandomGenre(), FLinearColor::MakeRandomColor() ,UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(50.f, 100.f), UKismetMathLibrary::RandomFloatInRange(50.f, 100.f));

			if (Index > 2) { Index = 0; }

			IdeaList.Insert(newIdea, Index);
			//TEST*** make method / optimize
			BacklogWidget->GetIdea(newIdea);
			BacklogWidget->DisplayNewIdea();

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

void AOfficeDepartment::HireProgrammer()
{
	if (SpawnWorker[0])
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;

			FVector SpawnLocation = FVector(0, 0, 270);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			World->SpawnActor<AEmployee>(SpawnWorker[0], SpawnLocation, SpawnRotation, SpawnParameters);
			//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Works");

		}

	}
}

void AOfficeDepartment::HireArtist()
{
	if (SpawnWorker[1])
	{
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;

			FVector SpawnLocation = FVector(0, 0, 270);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			World->SpawnActor<AEmployee>(SpawnWorker[1], SpawnLocation, SpawnRotation, SpawnParameters);
		}

	}
}
