// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_TurnBased_StartTurn.h"

UBFN_TurnBased_StartTurn::UBFN_TurnBased_StartTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = "TurnBased";
#endif
	
}

void UBFN_TurnBased_StartTurn::ExecuteInput(const FName& PinName)
{
	if(PinName == "In")
	{
		
	}
}

void UBFN_TurnBased_StartTurn::StartTurn()
{
	UBinaryTurnManagerComponent* TurnManagerComponent = GetBinaryTurnManagerComponent();
	check(TurnManagerComponent);

	FBinaryTurnAction CurrentTurnAction = TurnManagerComponent->GetCurrentTurnAction();
	
}
