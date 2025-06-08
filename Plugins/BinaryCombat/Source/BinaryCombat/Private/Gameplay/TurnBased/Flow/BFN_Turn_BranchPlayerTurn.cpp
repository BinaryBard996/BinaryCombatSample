// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_BranchPlayerTurn.h"

const FName UBFN_Turn_BranchPlayerTurn::INPIN_Evaluate = TEXT("Evaluate");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_Player = TEXT("Player");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_AI = TEXT("AI");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_Invalid = TEXT("InvalidTurn");

UBFN_Turn_BranchPlayerTurn::UBFN_Turn_BranchPlayerTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased|Logic");
	NodeDisplayStyle = FlowNodeStyle::Logic;
#endif
	InputPins.Empty();
	InputPins.Add(FFlowPin(INPIN_Evaluate));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(OUTPIN_Player));
	OutputPins.Add(FFlowPin(OUTPIN_AI));

	AllowedSignalModes = {EFlowSignalMode::Enabled, EFlowSignalMode::Disabled};
}

void UBFN_Turn_BranchPlayerTurn::ExecuteInput(const FName& PinName)
{
	const FBinaryTurnAction TurnAction = GetCurrentBinaryTurnAction();
	if(TurnAction.ActionType == EBinaryTurnActionType::Invalid || !IsValid(TurnAction.TurnPawn))
	{
		TriggerOutput(OUTPIN_Invalid);
	}
	else
	{
		// TODO.
		TriggerOutput(OUTPIN_Player);
	}
}
