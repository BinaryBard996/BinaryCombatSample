// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn_EndTurn.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"
#include "Kismet/GameplayStatics.h"

UBFN_Turn_EndTurn::UBFN_Turn_EndTurn(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased");
#endif
}

void UBFN_Turn_EndTurn::ExecuteInput(const FName& PinName)
{
	if (PinName == DefaultInputPin.PinName)
	{
		EndTurn();
		TriggerOutput(DefaultOutputPin.PinName, true);
	}
}

void UBFN_Turn_EndTurn::EndTurn()
{
	if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
	{
		FBinaryTurn CurrentTurn = TurnManagerComponent->GetCurrentTurn();
		if(CurrentTurn.IsValidTurn())
		{
			FBinaryTurnCommonMessage Message;
			Message.TurnActionData = CurrentTurn;

			UGameplayMessageSubsystem* MessageSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameplayMessageSubsystem>();
			MessageSubsystem->BroadcastMessage(BinaryCombatTags::Message_Turn_EndTurn, Message);
			MessageSubsystem->BroadcastMessageToActor(CurrentTurn.TurnPawn, BinaryCombatTags::Message_Turn_EndTurn, Message);
		}
	}
}
