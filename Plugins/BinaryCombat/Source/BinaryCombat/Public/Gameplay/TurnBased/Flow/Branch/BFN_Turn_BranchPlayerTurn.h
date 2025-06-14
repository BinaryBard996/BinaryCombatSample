// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn_BranchPlayerTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Branch Player Turn", KeyWords="TurnBased"))
class BINARYCOMBAT_API UBFN_Turn_BranchPlayerTurn : public UFlowNode
{
	GENERATED_BODY()

public:
	// FlowNode interface
	UBFN_Turn_BranchPlayerTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ExecuteInput(const FName& PinName) override;
	// ~FlowNode interface

	static const FName INPIN_Evaluate;
	static const FName OUTPIN_Player;
	static const FName OUTPIN_AI;
	static const FName OUTPIN_Invalid;
};
