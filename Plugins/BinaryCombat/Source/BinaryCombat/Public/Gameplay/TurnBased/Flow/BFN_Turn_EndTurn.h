// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn_EndTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName = "End Turn"))
class BINARYCOMBAT_API UBFN_Turn_EndTurn : public UFlowNode
{
	GENERATED_BODY()

	UBFN_Turn_EndTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	// FlowNode interface
	virtual void ExecuteInput(const FName& PinName) override;
	// ~FlowNode interface

protected:
	void EndTurn();
	
};
