// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_ProcessNewTurn.h"

#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#define START_NAME FName("Start")
#define NEW_TURN_NAME FName("NewTurn")
#define NO_VALID_TURN_NAME FName("InvalidTurn")

UBFN_Turn_ProcessNewTurn::UBFN_Turn_ProcessNewTurn(const FObjectInitializer& ObjectInitializer)
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

void UBFN_Turn_ProcessNewTurn::ExecuteInput(const FName& PinName)
{
	if(PinName == START_NAME)
	{
		ProcessNewTurn();
	}
}

void UBFN_Turn_ProcessNewTurn::ProcessNewTurn()
{
	UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this);
	if(!TurnManagerComponent)
	{
		TriggerOutput(NO_VALID_TURN_NAME);
		return;
	}
	
	TurnManagerComponent->ProcessNewTurn();	
	FBinaryTurn CurrentTurnAction = TurnManagerComponent->GetCurrentTurn();

	if(CurrentTurnAction.ActionType == EBinaryTurnActionType::Invalid)
	{
		TriggerOutput(NO_VALID_TURN_NAME);
		return;
	}

	TriggerOutput(NEW_TURN_NAME);
}
