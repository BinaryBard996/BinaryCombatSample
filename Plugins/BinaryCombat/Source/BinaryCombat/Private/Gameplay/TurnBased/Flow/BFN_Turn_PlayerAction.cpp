// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_PlayerAction.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnTypes.h"

const FName UBFN_Turn_PlayerAction::INPIN_Start = TEXT("Start");
const FName UBFN_Turn_PlayerAction::OUTPIN_End = TEXT("End");
const FName UBFN_Turn_PlayerAction::OUTPIN_Invalid = TEXT("InvalidAction");

UBFN_Turn_PlayerAction::UBFN_Turn_PlayerAction(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased");
	NodeDisplayStyle = FlowNodeStyle::Latent;
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

void UBFN_Turn_PlayerAction::Finish()
{
	Super::Finish();

	EndListeningPlayerAction();
}

void UBFN_Turn_PlayerAction::PlayerActionStart()
{
	FBinaryTurnAction CurrentTurnAction;
	bool bValidTurnAction = UBinaryTurnLibrary::GetCurrentTurnAction(this, CurrentTurnAction);

	if(!bValidTurnAction)
	{
		TriggerOutput(OUTPIN_Invalid);
		return;
	}

	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.BroadcastMessage(BinaryCombatTags::Message_Turn_PlayerActionStart, CurrentTurnAction);

	StartListeningPlayerAction();
}

void UBFN_Turn_PlayerAction::StartListeningPlayerAction()
{
	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	PlayerActionListenerHandle = GameplayMessageSubsystem.RegisterListener<FBinaryTurnPlayerAction>(BinaryCombatTags::Message_Turn_PlayerActionReceive,
		[this](FGameplayTag MessageTag, const FBinaryTurnPlayerAction& PlayerAction)
		{
			OnReceivePlayerAction(MessageTag, PlayerAction);
		},
		EGameplayMessageMatch::PartialMatch);
}

void UBFN_Turn_PlayerAction::EndListeningPlayerAction()
{
	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.UnregisterListener(PlayerActionListenerHandle);
}

void UBFN_Turn_PlayerAction::OnReceivePlayerAction(FGameplayTag MessageTag, const FBinaryTurnPlayerAction& PlayerAction)
{
	// TODO. Switch on different action.
	TriggerOutput(OUTPIN_End, true);
}
