// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/Flow/BFN_TurnBased.h"

#include "Kismet/GameplayStatics.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

UBinaryTurnManagerComponent* UBFN_TurnBased::GetBinaryTurnManagerComponent()
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
