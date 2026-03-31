// Fill out your copyright notice in the Description page of Project Settings.


#include "TacticalRPG/Public/BPFL_Utils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "../Unit/Unit.h"
#include "../Grid/Grid.h"


AUnit* UBPFL_Utils::GetUnitREF(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	AUnit* unit = Cast<AUnit>(
		UGameplayStatics::GetActorOfClass(WorldContextObject, AUnit::StaticClass()));
	
	if (!IsValid(unit)) return nullptr;
	return unit;
}

AGrid* UBPFL_Utils::GetGridREF(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	AGrid* grid = Cast<AGrid>(
		UGameplayStatics::GetActorOfClass(WorldContextObject, AGrid::StaticClass()));
	if (!IsValid(grid)) return nullptr;
	return grid;
}

void UBPFL_Utils::PrintString(float MessageTime, FColor MessageColor, const FString& Message)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, MessageTime, MessageColor, Message);
}
