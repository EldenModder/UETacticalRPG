// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include <string>

#include "Components/InstancedStaticMeshComponent.h"
#include "../Public/BPFL_Utils.h"



// Sets default values
AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISM"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ISM->SetupAttachment(Root);
	ISM->SetCollisionResponseToChannel(ECC_GRID, ECR_Block);
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	PC = GetWorld()->GetFirstPlayerController();
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PC->GetHitResultUnderCursor(ECC_GRID, false, Hit);
}

void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (ISM) ISM->ClearInstances();
	ISM->SetStaticMesh(GridMesh);
	ISM->SetMaterial(0, GridMaterial);
	ISM->NumCustomDataFloats = 3;
	ISM->OnClicked.AddDynamic(this, &AGrid::SetGridCellColorOnClick);
	ISM->OnClicked.AddDynamic(this, &AGrid::SpawnUnitOnCell);
	ISM->OnReleased.AddDynamic(this, &AGrid::SetGridCellColorBack);
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			int32 index = ISM->AddInstance(FTransform(
				GetActorRotation(),
		FVector(i * cellSize, j * cellSize, 0.f) + GetActorLocation(),
				GetActorScale3D()));
			SetGridCellColor(index, 1.f, 1.f, 1.f);
			GridIndexMap.Emplace(index, FIntPoint(i, j));
			GridCoordToIndex.Emplace(FIntPoint(i, j), index);
		}
	}
}

void AGrid::SetUnitToSpawn(AUnit* Unit)
{
	SelectedUnitClass = Unit->GetClass();
}

FIntPoint AGrid::GetGridPosition(AUnit* Unit)
{
	return Unit->UnitPosition;
}

void AGrid::SetGridCellColor(int index, float r, float g, float b) const
{
	ISM->SetCustomDataValue(index, 0, r);
	ISM->SetCustomDataValue(index, 1, g);
	ISM->SetCustomDataValue(index, 2, b);
}

void AGrid::SetGridCellColorOnClick(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed)
{
	int32 index = Hit.Item;
	if (index == INDEX_NONE) return;
	SetGridCellColor(Hit.Item, 1.f, 0.f, 0.f);
}

void AGrid::SetGridCellColorBack(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed)
{
	PC->GetHitResultUnderCursor(ECC_GRID, false, Hit);
	SetGridCellColor(Hit.Item, 1.f, 1.f, 1.f);
}

void AGrid::SpawnUnitOnCell(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed)
{
	if (Hit.Component == ClickedComponent)
	{
		int32 index = Hit.Item;
		FIntPoint GridCoord = GridIndexMap[index];
		HandleTileClicked(GridCoord);
	}
}

void AGrid::SpawnUnitAt(FIntPoint Coord)
{
	if (bCanSpawnUnit == false) return;
	if (OccupiedTiles.Contains(Coord) || !SelectedUnitClass)
	{
		return;
	}
	if (NumberOfUnitToSpawn <= 0)
	{
		bCanSpawnUnit = false; 
		return;
	}
	int32* indexPtr = GridCoordToIndex.Find(Coord);
	if (!indexPtr) return;
	
	int32 index = *indexPtr;
	
	FTransform instanceTransform;
	ISM->GetInstanceTransform(index, instanceTransform, true);
	
	FVector WorldPos = instanceTransform.GetLocation() + FVector(0,0,100.f);
	
	AUnit* Unit = GetWorld()->SpawnActor<AUnit>(
		SelectedUnitClass,
		WorldPos,
		FRotator::ZeroRotator
	);
	Unit->UnitPosition = Coord;
	OccupiedTiles.Emplace(Coord, Unit);
	NumberOfUnitToSpawn--;
}

void AGrid::HandleTileClicked(FIntPoint Coord)
{
	SpawnUnitAt(Coord);
}


