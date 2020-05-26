// Fill out your copyright notice in the Description page of Project Settings.


#include "Idea.h"

float Idea::GetWorkload()
{
	return 1.0f;//Replace with random
}

Idea::Idea(float chance, float pWorkload, float aWorkload)
{
	IdeaName = "Random Name";
	IdeaDescription = "Random Description";
	//Genre = EGenre::ADVENTURE;
	SuccessChance = chance;
	ProgrammerWorkload = pWorkload;
	ArtistWorkload = aWorkload;
}

Idea::Idea(FString name, FString description, FString mainWeight, EGenre genre, float chance, float programmerWorkload, float artistWorkload) 
{
	IdeaName = name;
	IdeaDescription = description;
	MainWeight = mainWeight;
	Genre = genre;
	SuccessChance = chance;
	ProgrammerWorkload = programmerWorkload;
	ArtistWorkload = artistWorkload;
}
