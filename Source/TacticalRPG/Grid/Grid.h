// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define ECC_GRID ECC_GameTraceChannel1

#include "CoreMinimal.h"
#include "../Unit/Unit.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class TACTICALRPG_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Construction Script
	virtual void OnConstruction(const FTransform& Transform) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float cellSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UStaticMesh* GridMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UMaterial* GridMaterial;
	UPROPERTY(BlueprintReadOnly)
	FHitResult Hit;
	
	UPROPERTY(BlueprintReadWrite, Category = "Grid")
	UInstancedStaticMeshComponent* ISM;
	UPROPERTY()
	APlayerController* PC;
	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY()
	TMap<int32, FIntPoint> GridIndexMap;
	UPROPERTY()
	TMap<FIntPoint, int32> GridCoordToIndex;
	UPROPERTY()
	TMap<FIntPoint, AUnit*> OccupiedTiles;
	
//-----------------------------------------------------------------------------	
	UFUNCTION(Category="Grid")
	FIntPoint GetGridPosition(AUnit* Unit);
	
private:
	UFUNCTION()
	void SetGridCellColor(int index, float r, float g, float b) const;
	UFUNCTION()
	void SetGridCellColorOnClick(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed);
	UFUNCTION()
	void SetGridCellColorBack(UPrimitiveComponent* ClickedComponent, FKey ButtonPressed);
	
	
};
