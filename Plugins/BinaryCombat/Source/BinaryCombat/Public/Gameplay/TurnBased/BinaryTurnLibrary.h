// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BinaryTurnLibrary.generated.h"

struct FBinaryTurn;
class UBinaryTurnManagerComponent;
/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryTurnLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Turn Gameplay", meta=(WorldContext="WorldContextObject"))
	static UBinaryTurnManagerComponent* GetBinaryTurnManagerComponent(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="Turn Gameplay", meta=(WorldContext="WorldContextObject", ExpandBoolAsExecs=ReturnValue))
	static bool GetCurrentTurn(UObject* WorldContextObject, FBinaryTurn& OutTurn);
};
