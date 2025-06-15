// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/Branch/BFN_Turn_BranchPlayerTurn.h"

#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnTypes.h"

const FName UBFN_Turn_BranchPlayerTurn::INPIN_Evaluate = TEXT("Evaluate");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_Player = TEXT("Player");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_AI = TEXT("AI");
const FName UBFN_Turn_BranchPlayerTurn::OUTPIN_Invalid = TEXT("InvalidTurn");

UBFN_Turn_BranchPlayerTurn::UBFN_Turn_BranchPlayerTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased|Branch");
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
	FBinaryTurn TurnAction;
	bool bValidTurnAction = UBinaryTurnLibrary::GetCurrentTurn(this, TurnAction);
	if(!bValidTurnAction)
	{
		TriggerOutput(OUTPIN_Invalid, true);
	}
	else
	{
		// TODO.
		TriggerOutput(OUTPIN_Player, true);
	}
}
