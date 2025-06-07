// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_TurnBased_ProcessNewTurn.h"

#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#define START_NAME FName("Start")
#define NEW_TURN_NAME FName("NewTurn")
#define NO_VALID_TURN_NAME FName("NoValidTurn")

UBFN_TurnBased_ProcessNewTurn::UBFN_TurnBased_ProcessNewTurn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category=TEXT("TurnBased");
#endif
	InputPins.Empty();
	InputPins.Add(FFlowPin(START_NAME));
	OutputPins.Empty();
	OutputPins.Add(FFlowPin(NEW_TURN_NAME));
	OutputPins.Add(FFlowPin(NO_VALID_TURN_NAME));
}

void UBFN_TurnBased_ProcessNewTurn::ExecuteInput(const FName& PinName)
{
	if(PinName == START_NAME)
	{
		ProcessNewTurn();
	}
}

void UBFN_TurnBased_ProcessNewTurn::ProcessNewTurn()
{
	UBinaryTurnManagerComponent* TurnManagerComponent = GetBinaryTurnManagerComponent();
	if(!TurnManagerComponent)
	{
		TriggerOutput(NO_VALID_TURN_NAME);
		return;
	}
	
	TurnManagerComponent->ProcessNewTurn();	
	FBinaryTurnAction CurrentTurnAction = TurnManagerComponent->GetCurrentTurnAction();

	if(CurrentTurnAction.ActionType == EBinaryTurnActionType::Invalid)
	{
		TriggerOutput(NO_VALID_TURN_NAME);
		return;
	}

	TriggerOutput(NEW_TURN_NAME);
}
