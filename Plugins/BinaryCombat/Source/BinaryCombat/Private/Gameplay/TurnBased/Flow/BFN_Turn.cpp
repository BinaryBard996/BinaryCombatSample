// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_Turn.h"

#include "Kismet/GameplayStatics.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

UBinaryTurnManagerComponent* UBFN_Turn::GetBinaryTurnManagerComponent()
{
	if(!IsValid(CacheBinaryTurnManagerComponent))
	{
		if(AGameStateBase* GameState = UGameplayStatics::GetGameState(this))
		{
			CacheBinaryTurnManagerComponent = GameState->FindComponentByClass<UBinaryTurnManagerComponent>();
		}
	}

	check(CacheBinaryTurnManagerComponent);
	return CacheBinaryTurnManagerComponent;
}

FBinaryTurnAction UBFN_Turn::GetCurrentBinaryTurnAction()
{
	if(UBinaryTurnManagerComponent* TurnManagerComponent = GetBinaryTurnManagerComponent())
	{
		return TurnManagerComponent->GetCurrentTurnAction();
	}

	return FBinaryTurnAction();
}
