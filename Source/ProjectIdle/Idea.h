// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EGenre : uint8
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

	EGenre Genre;

	FString IdeaName;
	FString IdeaDescription;
	FLinearColor CoverColor;

	FString MainWeight;
	float SuccessChance;
	float ProgrammerWorkload;
	float ArtistWorkload;

	class UIdeaButton* IdeaButton;

public:
	Idea(float chance, float pWorkload, float aWorkload);

	Idea(FString name, FString description, EGenre genre, FLinearColor CoverColor, float chance, float programmerWorkload, float artistWorkload);

public:
	static EGenre GetRandomGenre();
	static FText GenreToText(EGenre genre);

	float GetWorkload();
};
