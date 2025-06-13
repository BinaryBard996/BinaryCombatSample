// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/Graph/FlowNode_SubGraph.h"
#include "BFN_Turn_ActionGraph.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBFN_Turn_ActionGraph : public UFlowNode_SubGraph
{
	GENERATED_BODY()

public:

protected:
	// FlowNode interface
	virtual void ExecuteInput(const FName& PinName) override;
	// ~FlowNode interface
};
