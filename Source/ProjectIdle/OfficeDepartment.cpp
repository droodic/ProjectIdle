// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "Widgets/IdeaBacklogWidget.h"
#include "CeoDepMenuWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

Idea AOfficeDepartment::GenerateIdeaValues()
{
	//Later find random name, description, etc
	return Idea(UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f), UKismetMathLibrary::RandomFloatInRange(0.f, 100.f));
}

void AOfficeDepartment::BeginPlay()
{
	Super::BeginPlay();

	if (UserWidgets[0] != nullptr)
	{
		BacklogWidget = CreateWidget<UIdeaBacklogWidget>(GetWorld(), UserWidgets[0]);
		BacklogWidget->OfficeDepartment = this;
	}
	if (UserWidgets[1] != nullptr)
	{
		OfficeDepMenuWidget = CreateWidget<UCeoDepMenuWidget>(GetWorld(), UserWidgets[1]);
		OfficeDepMenuWidget->OfficeDepartment = this;
	}
}

void AOfficeDepartment::ViewBacklog()
{
	if (BacklogWidget != nullptr)
	{
		OfficeDepMenuWidget->RemoveFromParent();
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
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, "!!!");
	if (IsGenerating && CurrIdeaProgress <= MaxIdeaProgress)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "???");
		CurrIdeaProgress += DeltaTime * 15; // + DeltaTime * SpeedModifer (? - Have some algorithm to be able to scale this)
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
	if (OtherActor != nullptr && Cast<AProjectIdleCharacter>(OtherActor))
	{
		if (OfficeDepMenuWidget != nullptr)
		{
			OfficeDepMenuWidget->AddToViewport();
		}
	}
}

void AOfficeDepartment::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor != nullptr && Cast<AProjectIdleCharacter>(OtherActor))
	{
		if (OfficeDepMenuWidget->IsInViewport())
		{
			OfficeDepMenuWidget->RemoveFromParent();
		}
		else if (BacklogWidget->IsInViewport()) 
		{
			BacklogWidget->RemoveFromParent();
		}
	}
}
