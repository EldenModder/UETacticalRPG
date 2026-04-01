// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSpawner.h"

#include "BPFL_Utils.h"
#include "../Grid/Grid.h"
#include "Unit.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AUnitSpawner::AUnitSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GridInstance = UBPFL_Utils::GetGridREF(this);
}

// Called when the game starts or when spawned
void AUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (bCanSpawnUnit)
		GridInstance->ISM->OnClicked.AddDynamic(this, &AUnitSpawner::SpawnUnitOnCell);
}

void AUnitSpawner::SetUnitToSpawn(AUnit* Unit)
{
	SelectedUnitClass = Unit->GetClass();
}

void AUnitSpawner::SpawnUnitAt(FIntPoint Coord)
{
	if (bCanSpawnUnit == false) return;
	if (GridInstance->OccupiedTiles.Contains(Coord) || !SelectedUnitClass)
	{
		return;
	}
	if (NumberOfUnitToSpawn <= 0)
	{
		bCanSpawnUnit = false; 
		return;
	}
	int32* indexPtr = GridInstance->GridCoordToIndex.Find(Coord);
	if (!indexPtr) return;
	
	int32 index = *indexPtr;
	
	FTransform instanceTransform;
	GridInstance->ISM->GetInstanceTransform(index, instanceTransform, true);
	
	FVector WorldPos = instanceTransform.GetLocation() + FVector(0,0,100.f);
	
	AUnit* Unit = GetWorld()->SpawnActor<AUnit>(
		SelectedUnitClass,
		WorldPos,
		FRotator::ZeroRotator
	);
	Unit->UnitPosition = Coord;
	GridInstance->OccupiedTiles.Emplace(Coord, Unit);
	NumberOfUnitToSpawn--;
}

void AUnitSpawner::HandleTileClicked(FIntPoint Coord)
{
	SpawnUnitAt(Coord);
}

void AUnitSpawner::SpawnUnitOnCell(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed)
{
	if (GridInstance->Hit.Component == ClickedComponent)
	{
		int32 index = GridInstance->Hit.Item;
		FIntPoint GridCoord = GridInstance->GridIndexMap[index];
		HandleTileClicked(GridCoord);
	}
}

