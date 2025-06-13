// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#include "BinaryCombatLog.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

void UBinaryTurnManagerComponent::ClearTurnSystem()
{
	TurnItems.Reset();
	Turns.Reset();
}

void UBinaryTurnManagerComponent::AddTurnPawn(APawn* TurnPawn)
{
	if(!IsValid(TurnPawn))
	{
		UE_LOG(LogBinaryTurn, Error, TEXT("UBinaryTurnManagerComponent::AddTurnPawn-TurnPawn is not valid!"))
	}

	UBinaryPawnTurnComponent* PawnTurnComponent = TurnPawn->FindComponentByClass<UBinaryPawnTurnComponent>();
	if(!PawnTurnComponent)
	{
		UE_LOG(LogBinaryTurn, Error, TEXT("UBinaryTurnManagerComponent::AddTurnPawn-TurnPawn %s do not have turn component!"), *TurnPawn->GetName())
	}
	
	FBinaryTurnItem TurnItem;
	TurnItem.TurnPawn = TurnPawn;
	TurnItem.PawnTurnComponent = PawnTurnComponent;
	TurnItems.Emplace(TurnItem);
}

void UBinaryTurnManagerComponent::RemoveTurnPawn(APawn* TurnPawn)
{
	TurnItems.RemoveAll([TurnPawn](const FBinaryTurnItem& TurnItem)
	{
		return TurnPawn == TurnItem.TurnPawn;
	});
}

void UBinaryTurnManagerComponent::ProcessNewTurn()
{
	if(Turns.IsEmpty())
	{
		GenerateTurnQueue();
	}

	if(!Turns.IsEmpty())
	{
		CurrentTurn = Turns.Pop();
	}
	else
	{
		CurrentTurn = FBinaryTurn();
	}
}

FBinaryTurn UBinaryTurnManagerComponent::GetCurrentTurn() const
{
	return CurrentTurn;
}

void UBinaryTurnManagerComponent::GenerateTurnQueue()
{
	TArray<FBinaryTurn> PendingTurns;
	for(const auto& TurnItem: TurnItems)
	{
		FBinaryTurn TurnAction;
		TurnAction.TurnPawn = TurnItem.TurnPawn;
		TurnAction.PawnTurnComponent = TurnItem.PawnTurnComponent;
		TurnAction.ActionType = EBinaryTurnActionType::Default;
		PendingTurns.Emplace(TurnAction);
	}

	PendingTurns.Sort([](const FBinaryTurn& TurnActionA, const FBinaryTurn& TurnActionB)
	{
		const float SpeedA = IsValid(TurnActionA.PawnTurnComponent) ? TurnActionA.PawnTurnComponent->GetTurnSpeed() : 0.f;
		const float SpeedB = IsValid(TurnActionB.PawnTurnComponent) ? TurnActionB.PawnTurnComponent->GetTurnSpeed() : 0.f;
		return SpeedA >= SpeedB;
	});

	Turns.Append(PendingTurns);
}

bool UBinaryTurnManagerComponent::PopTurnAction(FBinaryTurnAction& TurnAction)
{
	if(PendingTurnActions.IsEmpty())
	{
		CurrentTurnAction.Reset();
		return false;
	}

	TurnAction = PendingTurnActions.Pop();
	CurrentTurnAction = TurnAction;
	return true;
}

void UBinaryTurnManagerComponent::PushTurnAction(const FBinaryTurnAction& TurnAction)
{
	PendingTurnActions.Emplace(TurnAction);
}

bool UBinaryTurnManagerComponent::GetCurrentTurnAction(FBinaryTurnAction& TurnAction)
{
	TurnAction = CurrentTurnAction;
	return TurnAction.IsValidTurnAction();
}
