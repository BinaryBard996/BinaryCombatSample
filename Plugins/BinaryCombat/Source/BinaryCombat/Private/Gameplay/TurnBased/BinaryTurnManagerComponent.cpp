// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryTurnManagerComponent.h"

#include "BinaryCombatLog.h"
#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

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

void UBinaryTurnManagerComponent::UpdateTurnBar()
{
	TurnItems.Sort([](const FBinaryTurnItem& TurnItemA, const FBinaryTurnItem& TurnItemB)
	{
		float SpeedA = IsValid(TurnItemA.PawnTurnComponent) ? TurnItemA.PawnTurnComponent->GetTurnSpeed() : 0.f;
		float SpeedB = IsValid(TurnItemB.PawnTurnComponent) ? TurnItemB.PawnTurnComponent->GetTurnSpeed() : 0.f;
		return SpeedA >= SpeedB;
	});

	if(ReadyTurns.IsEmpty())
	{
		ReadyTurns = TurnItems;
	}
}

bool UBinaryTurnManagerComponent::GetCurrentTurnItem(FBinaryTurnItem& CurrentTurnItem) const
{
	if(!ReadyTurns.IsEmpty())
	{
		CurrentTurnItem = ReadyTurns.Top();
		return true;
	}
	return false;
}
