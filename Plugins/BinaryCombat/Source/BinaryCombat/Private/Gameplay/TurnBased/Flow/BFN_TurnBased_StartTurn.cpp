// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_TurnBased_StartTurn.h"

#include "BinaryCombatLog.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

#define START_PIN_NAME FName("In")
#define END_PIN_NAME FName("Out")

UBFN_TurnBased_StartTurn::UBFN_TurnBased_StartTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = "TurnBased";
#endif
	
}

void UBFN_TurnBased_StartTurn::ExecuteInput(const FName& PinName)
{
	if(PinName == START_PIN_NAME)
	{
		StartTurn();
	}
}

void UBFN_TurnBased_StartTurn::StartTurn()
{
	UBinaryTurnManagerComponent* TurnManagerComponent = GetBinaryTurnManagerComponent();
	check(TurnManagerComponent);

	FBinaryTurnAction CurrentTurnAction = TurnManagerComponent->GetCurrentTurnAction();
	if(CurrentTurnAction.ActionType == EBinaryTurnActionType::Invalid)
	{
		UE_LOG(LogBinaryTurn, Error, TEXT("StartTurn-Invalid action"))
		TriggerOutput(END_PIN_NAME);
		return;
	}

	if(!IsValid(CurrentTurnAction.TurnPawn) || !IsValid(CurrentTurnAction.PawnTurnComponent))
	{
		UE_LOG(LogBinaryTurn, Error, TEXT("StartTurn-Invalid TurnPawn"))
		TriggerOutput(END_PIN_NAME);
		return;
	}

	CurrentTurnAction.PawnTurnComponent->OnStartTurn();
	TriggerOutput(END_PIN_NAME);
}
