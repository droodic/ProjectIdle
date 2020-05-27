// Fill out your copyright notice in the Description page of Project Settings.


#include "Idea.h"
#include "Kismet/KismetMathLibrary.h"

Idea::Idea(float chance, float pWorkload, float aWorkload)
{
	IdeaName = "Random Name";
	IdeaDescription = "Random Description";
	//Genre = EGenre::ADVENTURE;
	SuccessChance = chance;
	ProgrammerWorkload = pWorkload;
	ArtistWorkload = aWorkload;
}

Idea::Idea(FString name, FString description, /*FString mainWeight,*/ EGenre genre, FLinearColor coverColor,float chance, float programmerWorkload, float artistWorkload)
{
	IdeaName = name;
	IdeaDescription = description;
	//MainWeight = mainWeight;
	Genre = genre;
	CoverColor = coverColor;
	SuccessChance = chance;
	ProgrammerWorkload = programmerWorkload;
	ArtistWorkload = artistWorkload;
}

float Idea::GetWorkload()
{
	return 1.0f;//Replace with random
}

EGenre Idea::GetRandomGenre()
{
	auto randomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 5);

	switch (randomNumber)
	{
	case 0:
		return EGenre::ACTION;
		break;
	case 1:
		return EGenre::ADVENTURE;
		break;
	case 2:
		return EGenre::FPS;
		break;
	case 3:
		return EGenre::HORROR;
		break;
	case 4:
		return EGenre::PUZZLE;
		break;
	case 5:
		return EGenre::RPG;
		break;
	}

	return EGenre::ACTION;
}

FText Idea::GenreToText(EGenre genre)
{
	FText text;
	switch (genre)
	{
	case EGenre::ACTION:
		text = FText::FromString("Action");
		break;
	case EGenre::FPS:
		text = FText::FromString("FPS");
		break;
	case EGenre::PUZZLE:
		text = FText::FromString("Puzzle");
		break;
	case EGenre::ADVENTURE:
		text = FText::FromString("Advencture");
		break;
	case EGenre::HORROR:
		text = FText::FromString("Horror");
		break;
	case EGenre::RPG:
		text = FText::FromString("RPG");
		break;
	}

	return text;
}