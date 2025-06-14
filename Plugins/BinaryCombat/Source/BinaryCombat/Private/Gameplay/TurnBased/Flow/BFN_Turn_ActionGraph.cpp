// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/TurnBased/Flow/BFN_Turn_ActionGraph.h"
#include "Gameplay/TurnBased/BinaryTurnLibrary.h"
#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#include "Gameplay/TurnBased/BinaryTurnSettings.h"

UBFN_Turn_ActionGraph::UBFN_Turn_ActionGraph(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("TurnBased");
#endif
}

void UBFN_Turn_ActionGraph::ExecuteInput(const FName& PinName)
{
	Asset = nullptr;
	
	if(!IsPendingActionEmpty())
	{
		if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
		{
			FBinaryTurnAction TurnAction;
			TurnManagerComponent->PopTurnAction(TurnAction);

			if(TurnAction.IsValidTurnAction() && GetDefault<UBinaryTurnSettings>()->TurnFlowAssets.Contains(TurnAction.ActionType))
			{
				Asset = *GetDefault<UBinaryTurnSettings>()->TurnFlowAssets.Find(TurnAction.ActionType);
				Super::ExecuteInput(PinName);
				return;
			}
		}
	}
	
	TriggerOutput(FinishPin.PinName);
}

void UBFN_Turn_ActionGraph::Cleanup()
{
	Super::Cleanup();
}

bool UBFN_Turn_ActionGraph::IsPendingActionEmpty()
{
	if(UBinaryTurnManagerComponent* TurnManagerComponent = UBinaryTurnLibrary::GetBinaryTurnManagerComponent(this))
	{
		return TurnManagerComponent->IsPendingTurnActionEmpty();
	}

	return false;
}
