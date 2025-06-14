// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn_BranchAction.generated.h"

/**
 * 判断是否还有队列中的TurnAction
 */
UCLASS(meta=(DisplayName = "Check Action"))
class BINARYCOMBAT_API UBFN_Turn_BranchAction : public UFlowNode
{
	GENERATED_BODY()

public:
	UBFN_Turn_BranchAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// FlowNode interface
	virtual void ExecuteInput(const FName& PinName) override;
	// ~FlowNode interface

	static const FName INPIN_Evaluate;
	static const FName OUTPIN_True;
	static const FName OUTPIN_False;
};
