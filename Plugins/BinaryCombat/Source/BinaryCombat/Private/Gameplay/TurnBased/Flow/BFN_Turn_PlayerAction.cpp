// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_PlayerAction.h"

#include "GameFramework/GameplayMessageSubsystem.h"

const FName UBFN_Turn_PlayerAction::INPIN_Start = TEXT("Start");
const FName UBFN_Turn_PlayerAction::OUTPIN_End = TEXT("End");

UBFN_Turn_PlayerAction::UBFN_Turn_PlayerAction(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased");
#endif
	InputPins.Empty();
	InputPins.Emplace(INPIN_Start);

	OutputPins.Empty();
	OutputPins.Emplace(OUTPIN_End);
}

void UBFN_Turn_PlayerAction::ExecuteInput(const FName& PinName)
{
	if(PinName == INPIN_Start)
	{
		PlayerActionStart();
	}
}

void UBFN_Turn_PlayerAction::PlayerActionStart()
{
	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.BroadcastMessage(BinaryCombatTags::Message_Turn_PlayerActionStart, GetCurrentBinaryTurnAction());

	
}
