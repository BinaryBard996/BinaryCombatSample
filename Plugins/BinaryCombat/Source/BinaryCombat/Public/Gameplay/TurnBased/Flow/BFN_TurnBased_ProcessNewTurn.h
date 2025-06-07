// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BFN_TurnBased.h"
#include "Nodes/FlowNode.h"
#include "BFN_TurnBased_ProcessNewTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Process New Turn", Keywords="TurnBased"))
class BINARYCOMBAT_API UBFN_TurnBased_ProcessNewTurn : public UBFN_TurnBased
{
	GENERATED_BODY()

public:
	UBFN_TurnBased_ProcessNewTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ExecuteInput(const FName& PinName) override;

	void ProcessNewTurn();
	
};
