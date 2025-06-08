// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TurnBased/Flow/BFN_Turn.h"
#include "BFN_Turn_PlayerAction.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Player Action", KeyWords="TurnBased"))
class BINARYCOMBAT_API UBFN_Turn_PlayerAction : public UBFN_Turn
{
	GENERATED_BODY()

public:
	// FlowNode interface
	UBFN_Turn_PlayerAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ExecuteInput(const FName& PinName) override;
	// ~FlowNode interface

	void PlayerActionStart();
	
	static const FName INPIN_Start;
	static const FName OUTPIN_End;
};
