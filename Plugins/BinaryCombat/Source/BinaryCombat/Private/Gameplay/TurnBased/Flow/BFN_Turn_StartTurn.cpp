// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_StartTurn.h"

#include "BinaryCombatLog.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"
#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"
#include "Gameplay/TurnBased/BinaryTurnTypes.h"
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
		TriggerOutput(END_PIN_NAME, true);
	}
}

void UBFN_Turn_StartTurn::StartTurn()
{
	if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
	{
		FBinaryTurn CurrentTurn = TurnManagerComponent->GetCurrentTurn();
		if(CurrentTurn.IsValidTurn())
		{
			FBinaryTurnCommonMessage Message;
			Message.TurnActionData = CurrentTurn;

			UGameplayMessageSubsystem* MessageSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameplayMessageSubsystem>();
			MessageSubsystem->BroadcastMessage(BinaryCombatTags::Message_Turn_StartTurn, Message);
			MessageSubsystem->BroadcastMessageToActor(CurrentTurn.TurnPawn, BinaryCombatTags::Message_Turn_StartTurn, Message);
		}
	}
}
