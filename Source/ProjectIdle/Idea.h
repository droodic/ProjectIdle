// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EGenre : int16
{
	ACTION,
	FPS,
	PUZZLE,
	ADVENTURE,
	HORROR,
	RPG
};

/**
 *
 */
class PROJECTIDLE_API Idea
{

public:
	class UImage* IdeaCover;

	TEnumAsByte<EGenre> Genre;

	FString IdeaName;
	FString IdeaDescription;
	FLinearColor CoverColor;

	FString MainWeight;
	float SuccessChance;
	float ProgrammerWorkload;
	float ArtistWorkload;


public:
	Idea(float chance, float pWorkload, float aWorkload);

	Idea(FString name, FString description,/*FString MainWeight,*/ EGenre genre, FLinearColor CoverColor, float chance, float programmerWorkload, float artistWorkload);

public:
	static EGenre GetRandomGenre();
	static FText GenreToText(EGenre genre);

	float GetWorkload();
};
