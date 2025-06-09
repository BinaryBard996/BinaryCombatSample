// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryTurnLibrary.h"

#include "BinaryCombatLog.h"
#include "GameFramework/GameStateBase.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"
#include "Kismet/GameplayStatics.h"

UBinaryTurnManagerComponent* UBinaryTurnLibrary::GetBinaryTurnManagerComponent(UObject* WorldContextObject)
{
	if(AGameStateBase* GameState = UGameplayStatics::GetGameState(WorldContextObject))
	{
		return GameState->FindComponentByClass<UBinaryTurnManagerComponent>();
	}

	UE_LOG(LogBinaryTurn, Error, TEXT("GetBinaryTurnManagerComponent-No TurnManagerComponent for game state, please check!"))
	return nullptr;
}

bool UBinaryTurnLibrary::GetCurrentTurnAction(UObject* WorldContextObject, FBinaryTurnAction& OutTurnAction)
{
	if(UBinaryTurnManagerComponent* TurnManagerComponent = GetBinaryTurnManagerComponent(WorldContextObject))
	{
		OutTurnAction = TurnManagerComponent->GetCurrentTurnAction();
		if(OutTurnAction.ActionType != EBinaryTurnActionType::Invalid)
		{
			return true;
		}
	}

	UE_LOG(LogBinaryTurn, Error, TEXT("GetCurrentTurnAction-No valid current turn action, please check!"))
	return false;
}
