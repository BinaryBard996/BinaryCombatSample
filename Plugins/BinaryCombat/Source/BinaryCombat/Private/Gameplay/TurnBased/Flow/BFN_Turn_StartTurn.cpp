// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_StartTurn.h"

#include "BinaryCombatLog.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"
#include "Kismet/GameplayStatics.h"

#define START_PIN_NAME FName("In")
#define END_PIN_NAME FName("Out")

UBFN_Turn_StartTurn::UBFN_Turn_StartTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = "TurnBased";
#endif
	
}

void UBFN_Turn_StartTurn::ExecuteInput(const FName& PinName)
{
	if(PinName == START_PIN_NAME)
	{
		StartTurn();
	}
}

void UBFN_Turn_StartTurn::StartTurn()
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

	if(!IsValid(CurrentTurnAction.TurnPawn))
	{
		UE_LOG(LogBinaryTurn, Error, TEXT("StartTurn-Invalid TurnPawn"))
		TriggerOutput(END_PIN_NAME);
		return;
	}

	FBinaryTurnCommonMessage Message;
	Message.TurnActionData = CurrentTurnAction;

	UGameplayMessageSubsystem* MessageSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameplayMessageSubsystem>();
	MessageSubsystem->BroadcastMessageToActor(CurrentTurnAction.TurnPawn, BinaryCombatTags::Message_Turn_StartTurn, Message);
	
	TriggerOutput(END_PIN_NAME);
}
