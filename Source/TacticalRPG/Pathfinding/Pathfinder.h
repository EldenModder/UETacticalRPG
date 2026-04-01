// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pathfinder.generated.h"

UCLASS()
class TACTICALRPG_API APathfinder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APathfinder();
	static APathfinder* Instance;
	
private:
	const int32 MOVE_STRAIGHT_COST = 10;
	int32 width, height;
	
};
