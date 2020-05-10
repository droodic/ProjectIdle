// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTIDLE_API Idea
{

public:
	FString IdeaName;
	float ChanceOfSuccess;
	float ProgrammerWorkload;
	float ArtistWorkload;


	float GetWorkload();

	Idea();
};
