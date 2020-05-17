// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"
#include "Idea.h"
#include "CeoDepMenuWidget.h"
#include "UI/IdeaGenerationUI.h"
#include "Components/WidgetComponent.h"

Idea AOfficeDepartment::GenerateIdeaValues()
{
	//Later find random name, description, etc
	return Idea(random.FRandRange(0, 100), random.FRandRange(0, 100), random.FRandRange(0, 100));
}

void AOfficeDepartment::BeginPlay()
{
	if (UserWidgets[0])
	{
		OfficeDepartmentUI = CreateWidget<UCeoDepMenuWidget>(GetWorld(), UserWidgets[0]);
	}
	if (UserWidgets[1])
	{
		IdeaGenerationWidget = CreateWidget<UIdeaGenerationUI>(GetWorld(), UserWidgets[1]);
	}
}

void AOfficeDepartment::GenerateIdea()
{
	IsGenerating = true;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Generating Idea");
	
	if (OfficeDepartmentUI)
	{
		OfficeDepartmentUI->RemoveFromParent();
	}
	if (IdeaGenerationWidget)
	{
		IdeaGenerationWidget->AddToViewport();
	}

	

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
	if (IsGenerating && CurrIdeaProgress <= MaxIdeaProgress)
	{
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
		if (OfficeDepartmentUI)
		{
			OfficeDepartmentUI->AddToViewport();
		}

	}
}

void AOfficeDepartment::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor != nullptr && Cast<AProjectIdleCharacter>(OtherActor))
	{
		if (OfficeDepartmentUI)
		{
			OfficeDepartmentUI->RemoveFromParent();
		}
	}
}
