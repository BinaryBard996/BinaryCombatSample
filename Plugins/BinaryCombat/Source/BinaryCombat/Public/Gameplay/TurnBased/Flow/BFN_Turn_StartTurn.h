// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TurnBased/Flow/BFN_Turn.h"
#include "BFN_Turn_StartTurn.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Start Turn", KeyWords="TurnBased"))
class BINARYCOMBAT_API UBFN_Turn_StartTurn : public UBFN_Turn
{
	GENERATED_BODY()

public:
	UBFN_Turn_StartTurn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void ExecuteInput(const FName& PinName) override;

	void StartTurn();
	
};
