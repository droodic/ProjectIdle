// Fill out your copyright notice in the Description page of Project Settings.


#include "Idea.h"

float Idea::GetWorkload()
{
	return 1.0f;//Replace with random
}

Idea::Idea(float chance, float pWorkload, float aWorkload)
{
	ChanceOfSuccess = chance;
	ProgrammerWorkload = pWorkload;
	ArtistWorkload = aWorkload;
}


//Idea::~Idea()
//{
//}
