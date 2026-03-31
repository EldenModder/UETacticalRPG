// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_Utils.generated.h"

/**
 * 
 */
class AUnit;
class AGrid;
UCLASS()
class TACTICALRPG_API UBPFL_Utils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "TacticalRPG|Utils", meta=(WorldContext = "WorldContextObject"))
	static AUnit* GetUnitREF(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "TacticalRPG|Utils", meta=(WorldContext = "WorldContextObject"))
	static AGrid* GetGridREF(const UObject* WorldContextObject);	
	UFUNCTION(Category = "TacticalRPG|Utils")
	static void PrintString(float MessageTime, FColor MessageColor, const FString& Message);
};
