#pragma once
#include "CoreMinimal.h"
#include "GridPosition.generated.h"

USTRUCT(BlueprintType)
struct FGridPosition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;
	
	FGridPosition() : X(0), Y(0) {}
	FGridPosition(int32 x, int32 y) : X(x), Y(y) {}
	
	bool operator==(const FGridPosition& pos) const
	{
		return X == pos.X && Y == pos.Y;
	}
	
	bool operator!=(const FGridPosition& pos) const
	{
		return !(*this == pos);
	}
	
	FGridPosition operator+(const FGridPosition& pos) const
	{
		return FGridPosition(X + pos.X, Y - pos.Y);
	}
	
	FGridPosition operator-(const FGridPosition& pos) const
	{
		return FGridPosition(X - pos.X, Y - pos.Y);
	}
	
	FString ToString() const
	{
		return FString::Printf(TEXT("x: %d; y: %d"), X, Y);
	}
};

inline uint32 GetTypeHash(const FGridPosition& pos)
{
	return HashCombine(GetTypeHash(pos.X), GetTypeHash(pos.Y));
}
