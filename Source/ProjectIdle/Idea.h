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

	EGenre Genre;

	FString IdeaName;
	FString IdeaDescription;
	FString MainWeight;

	float SuccessChance;
	float ProgrammerWorkload;
	float ArtistWorkload;

	float GetWorkload();

	Idea(float chance, float pWorkload, float aWorkload);

	Idea(FString name, FString description, FString mainWeight, EGenre genre, float chance, float programmerWorkload, float artistWorkload);
};
