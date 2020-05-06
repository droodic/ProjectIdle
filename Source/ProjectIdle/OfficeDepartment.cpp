// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeDepartment.h"

void AOfficeDepartment::GenerateIdea() 
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Generating Idea"));
	ideasGenerated++;
	//Enable widget call meeting btn if >1? 
}

void AOfficeDepartment::CallMeeting() 
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Emerald, TEXT("Meeting Called"));
	//move ai to meeting room, you meet them there to start progress
}