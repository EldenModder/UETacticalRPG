// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


struct FPathNode
{
private:
	FIntPoint GridPosition;
	int32 gCost = 0;
	int32 hCost = 0;
	int32 fCost = 0;

	FPathNode* CameFrom = nullptr;
	bool bIsWalkable = true;

public:
	FPathNode() = default;

	FPathNode(const FIntPoint& InGridPosition)
		: GridPosition(InGridPosition)
	{
	}

	FString ToString() const
	{
		return GridPosition.ToString();
	}

	// Getters
	int32 GetGCost() const { return gCost; }
	int32 GetHCost() const { return hCost; }
	int32 GetFCost() const { return fCost; }
	FIntPoint GetGridPosition() const { return GridPosition; }
	FPathNode* GetCameFrom() const { return CameFrom; }
	bool IsWalkable() const { return bIsWalkable; }

	// Setters
	void SetGCost(int32 InGCost) { gCost = InGCost; }
	void SetHCost(int32 InHCost) { hCost = InHCost; }
	void SetCameFrom(FPathNode* InNode) { CameFrom = InNode; }
	void SetIsWalkable(bool bWalkable) { bIsWalkable = bWalkable; }

	void CalculateFCost()
	{
		fCost = gCost + hCost;
	}

	void ResetCameFrom()
	{
		CameFrom = nullptr;
	}
};
