// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_PlayerMakeDecision.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"
#include "Gameplay/TurnBased/BinaryTurnTypes.h"

const FName UBFN_Turn_PlayerMakeDecision::INPIN_Start = TEXT("Start");
const FName UBFN_Turn_PlayerMakeDecision::OUTPIN_End = TEXT("MadeDecision");
const FName UBFN_Turn_PlayerMakeDecision::OUTPIN_Invalid = TEXT("InvalidAction");

UBFN_Turn_PlayerMakeDecision::UBFN_Turn_PlayerMakeDecision(const FObjectInitializer& ObjectInitializer)
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

void UBFN_Turn_PlayerMakeDecision::ExecuteInput(const FName& PinName)
{
	if(PinName == INPIN_Start)
	{
		PlayerActionStart();
	}
}

void UBFN_Turn_PlayerMakeDecision::Cleanup()
{
	Super::Cleanup();

	EndListeningPlayerAction();
}

void UBFN_Turn_PlayerMakeDecision::PlayerActionStart()
{
	FBinaryTurn CurrentTurnAction;
	bool bValidTurnAction = UBinaryTurnLibrary::GetCurrentTurnAction(this, CurrentTurnAction);

	if(!bValidTurnAction)
	{
		TriggerOutput(OUTPIN_Invalid);
		return;
	}

	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.BroadcastMessage(BinaryCombatTags::Message_Turn_PlayerMakeDecisionStart, CurrentTurnAction);

	StartListeningPlayerAction();
}

void UBFN_Turn_PlayerMakeDecision::StartListeningPlayerAction()
{
	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	PlayerActionListenerHandle = GameplayMessageSubsystem.RegisterListener<FBinaryTurnAction>(BinaryCombatTags::Message_Turn_PlayerMakeDecisionEnd,
		[this](FGameplayTag MessageTag, const FBinaryTurnAction& PlayerAction)
		{
			OnReceivePlayerAction(MessageTag, PlayerAction);
		},
		EGameplayMessageMatch::PartialMatch);
}

void UBFN_Turn_PlayerMakeDecision::EndListeningPlayerAction()
{
	auto& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.UnregisterListener(PlayerActionListenerHandle);
}

void UBFN_Turn_PlayerMakeDecision::OnReceivePlayerAction(FGameplayTag MessageTag, const FBinaryTurnAction& PlayerAction)
{
	// TODO. Switch on different action.
	if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
	{
		if(PlayerAction.IsValidTurnAction())
		{
			TurnManagerComponent->PushTurnAction(PlayerAction);
		}
	}

	TriggerOutput(OUTPIN_End);
}
