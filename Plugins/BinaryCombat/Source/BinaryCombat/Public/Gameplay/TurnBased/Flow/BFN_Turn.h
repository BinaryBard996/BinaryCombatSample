// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBFN_Turn : public UFlowNode
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Gameplay|TurnBased")
	UBinaryTurnManagerComponent* GetBinaryTurnManagerComponent();

	UFUNCTION(BlueprintCallable, Category="Gameplay|TurnBased")
	FBinaryTurnAction GetCurrentBinaryTurnAction();

protected:
	UPROPERTY()
	TObjectPtr<UBinaryTurnManagerComponent> CacheBinaryTurnManagerComponent;
};
