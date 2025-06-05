// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BinaryTurnTypes.h"
#include "Components/GameStateComponent.h"
#include "BinaryTurnManagerComponent.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryTurnManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	void AddTurnPawn(APawn* TurnPawn);
	void RemoveTurnPawn(APawn* TurnPawn);
	void UpdateActionBar();

protected:
	UPROPERTY()
	TArray<FBinaryTurnItem> ReadyTurns;
	
	UPROPERTY()
	TArray<FBinaryTurnItem> PendingTurns;
};
