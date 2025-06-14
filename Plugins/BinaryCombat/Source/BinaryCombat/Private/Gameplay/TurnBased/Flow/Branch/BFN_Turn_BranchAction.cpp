// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/Branch/BFN_Turn_BranchAction.h"

#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

const FName UBFN_Turn_BranchAction::INPIN_Evaluate = TEXT("Check Pending Action");
const FName UBFN_Turn_BranchAction::OUTPIN_True = TEXT("True");
const FName UBFN_Turn_BranchAction::OUTPIN_False = TEXT("False");

UBFN_Turn_BranchAction::UBFN_Turn_BranchAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased|Branch");
	NodeDisplayStyle = FlowNodeStyle::Logic;
#endif

	InputPins.Empty();
	InputPins.Add(FFlowPin(INPIN_Evaluate));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(OUTPIN_True));
	OutputPins.Add(FFlowPin(OUTPIN_False));

	AllowedSignalModes = {EFlowSignalMode::Enabled, EFlowSignalMode::Disabled};
}

void UBFN_Turn_BranchAction::ExecuteInput(const FName& PinName)
{
	if(PinName == INPIN_Evaluate)
	{
		if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
		{
			if(TurnManagerComponent->IsPendingTurnActionEmpty())
			{
				TriggerOutput(OUTPIN_False, true);
			}
			else
			{
				TriggerOutput(OUTPIN_True, true);
			}
		}
		else
		{
			TriggerOutput(OUTPIN_False, true);
		}
	}
	else
	{
		TriggerOutput(OUTPIN_False, true);
	}
}
