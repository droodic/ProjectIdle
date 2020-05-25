// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "Widgets/IdeaBacklogWidget.h"
#include "CeoDepMenuWidget.h"
#include "Components/WidgetComponent.h"
#include "GameManager.h"
#include "GameHUD.h"
#include "Kismet/KismetMathLibrary.h"

Idea AOfficeDepartment::GenerateIdeaValues()
{
	//Later find random name, description, etc
	return Idea(UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f));
}

void AOfficeDepartment::BeginPlay()
{
	Super::BeginPlay();
	//GM = GetWorld()->GetGameInstance<UGameManager>(); //unused
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

			//auto newIdea = IdeaList.Add(new Idea(GenerateIdeaValues())); //Use randomized values later

			auto newIdea = new Idea(GenerateIdeaValues());

			//TEST*** make method / optimize
			BacklogWidget->DisplayNewIdea();
			BacklogWidget->GetIdea(newIdea);
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
