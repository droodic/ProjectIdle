// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "Widgets/IdeaBacklogWidget.h"
#include "CeoDepMenuWidget.h"
#include "Components/WidgetComponent.h"

AOfficeDepartment::AOfficeDepartment() 
{
	
}

Idea AOfficeDepartment::GenerateIdeaValues()
{
	//Later find random name, description, etc
	return Idea(random.FRandRange(0, 100), random.FRandRange(0, 100), random.FRandRange(0, 100));
}

void AOfficeDepartment::BeginPlay()
{
	Super::BeginPlay();
	if (UserWidgets[0])
	{
		BacklogWidget = CreateWidget<UIdeaBacklogWidget>(GetWorld(), UserWidgets[0]);
	}
	if (UserWidgets[1])
	{
		OfficeDepMenuWidget = CreateWidget<UCeoDepMenuWidget>(GetWorld(), UserWidgets[1]);
		OfficeDepMenuWidget->OfficeDepartment = this;
	}
}

void AOfficeDepartment::ViewBacklog() 
{
	if (BacklogWidget)
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
	//	//emp->AI->GoMeeting();
	//}
	//move ai to meeting room, you meet them there to start progress
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
			IdeaList.Add(new Idea(GenerateIdeaValues())); //Use randomized values later
		}
	}
}

void AOfficeDepartment::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor != nullptr && Cast<AProjectIdleCharacter>(OtherActor))
	{
		if (OfficeDepMenuWidget)
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
		if (BacklogWidget->IsInViewport()) {
			BacklogWidget->RemoveFromParent();
		}
	}
}
