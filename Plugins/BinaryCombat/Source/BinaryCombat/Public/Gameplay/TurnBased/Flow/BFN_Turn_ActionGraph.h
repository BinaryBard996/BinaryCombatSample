// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/Graph/FlowNode_SubGraph.h"
#include "BFN_Turn_ActionGraph.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Turn Action Graph"))
class BINARYCOMBAT_API UBFN_Turn_ActionGraph : public UFlowNode_SubGraph
{
	GENERATED_BODY()

public:
	UBFN_Turn_ActionGraph(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// FlowNode interface
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;
	// ~FlowNode interface

	bool IsPendingActionEmpty();
	
};
