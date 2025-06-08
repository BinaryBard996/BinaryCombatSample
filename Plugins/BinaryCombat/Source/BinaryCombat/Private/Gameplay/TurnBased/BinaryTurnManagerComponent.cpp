// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#include "BinaryCombatLog.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

void UBinaryTurnManagerComponent::ClearTurnSystem()
{
	TurnItems.Reset();
	TurnActions.Reset();
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
	if(TurnActions.IsEmpty())
	{
		GenerateTurnActionQueue();
	}

	if(!TurnActions.IsEmpty())
	{
		CurrentTurnAction = TurnActions.Pop();
	}
	else
	{
		CurrentTurnAction = FBinaryTurnAction();
	}
}

FBinaryTurnAction UBinaryTurnManagerComponent::GetCurrentTurnAction() const
{
	return CurrentTurnAction;
}

void UBinaryTurnManagerComponent::GenerateTurnActionQueue()
{
	TArray<FBinaryTurnAction> PendingTurnActions;
	for(const auto& TurnItem: TurnItems)
	{
		FBinaryTurnAction TurnAction;
		TurnAction.TurnPawn = TurnItem.TurnPawn;
		TurnAction.PawnTurnComponent = TurnItem.PawnTurnComponent;
		TurnAction.ActionType = EBinaryTurnActionType::Default;
		PendingTurnActions.Emplace(TurnAction);
	}

	PendingTurnActions.Sort([](const FBinaryTurnAction& TurnActionA, const FBinaryTurnAction& TurnActionB)
	{
		const float SpeedA = IsValid(TurnActionA.PawnTurnComponent) ? TurnActionA.PawnTurnComponent->GetTurnSpeed() : 0.f;
		const float SpeedB = IsValid(TurnActionB.PawnTurnComponent) ? TurnActionB.PawnTurnComponent->GetTurnSpeed() : 0.f;
		return SpeedA >= SpeedB;
	});

	TurnActions.Append(PendingTurnActions);
}