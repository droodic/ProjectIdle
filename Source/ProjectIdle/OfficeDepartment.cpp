// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"

void AOfficeDepartment::GenerateIdea() 
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Generating Idea"));
	IsGenerating = true;
	
	//When idea gen complete



	//Enable widget call meeting btn if >1? 
}

void AOfficeDepartment::CallMeeting() 
{

	//for (AEmployee* emp : GM->EmployeeList) {
	//	//emp->AI->GoMeeting();
	//}
	//move ai to meeting room, you meet them there to start progress
}

void AOfficeDepartment::Tick(float DeltaTime)
{
	if (IsGenerating && CurrIdeaProgress <= MaxIdeaProgress)
	{
		CurrIdeaProgress+= DeltaTime * 3; // + DeltaTime * SpeedModifer (? - Have some algorithm to be able to scale this)
		if (CurrIdeaProgress >= MaxIdeaProgress) {
			IsGenerating = false;
			CurrIdeaProgress = 0;
			ideasGenerated++;
			IdeaList.Add(new Idea());
		}
	}
}
