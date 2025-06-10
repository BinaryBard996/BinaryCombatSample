// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Nodes/FlowNode.h"
#include "BFN_Turn_PlayerMakeDecision.generated.h"

struct FBinaryTurnPawnAction;
/**
 * 
 */
UCLASS(meta=(DisplayName="Player Make Decision", KeyWords="TurnBased"))
class BINARYCOMBAT_API UBFN_Turn_PlayerMakeDecision : public UFlowNode
{
	GENERATED_BODY()

public:
	UBFN_Turn_PlayerMakeDecision(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// FlowNode interface
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;
	// ~FlowNode interface

	void PlayerActionStart();

	void StartListeningPlayerAction();
	void EndListeningPlayerAction();

	void OnReceivePlayerAction(FGameplayTag MessageTag, const FBinaryTurnPawnAction& PlayerAction);

public:
	static const FName INPIN_Start;
	static const FName OUTPIN_End;
	static const FName OUTPIN_Invalid;

protected:
	FGameplayMessageListenerHandle PlayerActionListenerHandle;
};
