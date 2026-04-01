// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PathNode.generated.h"

/**
 * 
 */

UCLASS()
class TACTICALRPG_API UPathNode : public UObject
{
	GENERATED_BODY()
	
private:
	FIntPoint GridPosition;
	int32 gCost, hCost, fCost;
	UPROPERTY()
	UPathNode* CameFrom;
	bool bIsWalkable;
	
public:
	UPathNode(FIntPoint GridPosition) { this->GridPosition = GridPosition; }
	FString ToString() const { return GridPosition.ToString(); }
	
	int32 GetCost() const { return gCost; }
	int32 GetHCost() const { return hCost; }
	int32 GetFCost() const { return fCost; }
	bool IsWalkable() const { return bIsWalkable; }
	FIntPoint GetGridPosition() const { return GridPosition; }
	UPathNode* GetCameFrom() const { return CameFrom; }
	
	void SetGCost(int32 gCost) { this->gCost = gCost; }
	void SetHCost(int32 hCost) { this->hCost = hCost; }
	void SetCameFrom(UPathNode* CameFrom) { this->CameFrom = CameFrom; }
	bool SetIsWalkable(bool IsWalkable) { return this->bIsWalkable = IsWalkable; };
	void CalculateFCost() { fCost = gCost + hCost; };
	void ResetCameFrom() { CameFrom = nullptr; }
};
