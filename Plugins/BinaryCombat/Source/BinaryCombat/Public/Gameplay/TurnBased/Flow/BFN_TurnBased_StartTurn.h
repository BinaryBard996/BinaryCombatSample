// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TurnBased/Flow/BFN_TurnBased.h"
#include "BFN_TurnBased_StartTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Start Turn", KeyWords="TurnBased"))
class BINARYCOMBAT_API UBFN_TurnBased_StartTurn : public UBFN_TurnBased
{
	GENERATED_BODY()

public:
	UBFN_TurnBased_StartTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ExecuteInput(const FName& PinName) override;

	void StartTurn();
	
};
