// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitSpawner.generated.h"

class AUnit;
class AGrid;

UCLASS()
class TACTICALRPG_API AUnitSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnitSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bCanSpawnUnit = true;
	UPROPERTY(BlueprintReadWrite, Category = "Unit")
	TSubclassOf<AUnit> SelectedUnitClass;
	UPROPERTY()
	AGrid* GridInstance;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetUnitToSpawn(AUnit* Unit);
	
private:
	UPROPERTY()
	int NumberOfUnitToSpawn = 1;
	
	UFUNCTION()
	void SpawnUnitOnCell(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed);
	UFUNCTION()
	void SpawnUnitAt(FIntPoint Coord);
	UFUNCTION()
	void HandleTileClicked(FIntPoint Coord);
	
	
};
