// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn_ProcessNewTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Process New Turn", Keywords="TurnBased"))
class BINARYCOMBAT_API UBFN_Turn_ProcessNewTurn : public UFlowNode
{
	GENERATED_BODY()

public:
	UBFN_Turn_ProcessNewTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ExecuteInput(const FName& PinName) override;

	void ProcessNewTurn();
	
};
