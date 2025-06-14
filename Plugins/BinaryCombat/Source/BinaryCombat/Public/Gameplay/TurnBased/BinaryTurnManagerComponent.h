// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BinaryTurnTypes.h"
#include "Components/GameStateComponent.h"
#include "BinaryTurnManagerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(BinaryTurn), meta=(BlueprintSpawnableComponent))
class BINARYCOMBAT_API UBinaryTurnManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	// Turn Start
	UFUNCTION(BlueprintCallable)
	void ClearTurnSystem();

	UFUNCTION(BlueprintCallable)
	void AddTurnPawn(APawn* TurnPawn);

	UFUNCTION(BlueprintCallable)
	void RemoveTurnPawn(APawn* TurnPawn);

	UFUNCTION(BlueprintCallable)
	void ProcessNewTurn();

	UFUNCTION(BlueprintCallable)
	FBinaryTurn GetCurrentTurn() const;

	void GenerateTurnQueue();
	// ~Turn End

	// Turn Actions Start
	UFUNCTION(BlueprintCallable)
	bool PopTurnAction(FBinaryTurnAction& TurnAction);

	UFUNCTION(BlueprintCallable)
	void PushTurnAction(const FBinaryTurnAction& TurnAction);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs=ReturnValue))
	bool GetCurrentTurnAction(FBinaryTurnAction& TurnAction);

	UFUNCTION(BlueprintPure)
	bool IsPendingTurnActionEmpty() const;
	// ~Turn Actions End

protected:
	UPROPERTY()
	TArray<FBinaryTurn> Turns;
	
	UPROPERTY()
	TArray<FBinaryTurnItem> TurnItems;

	UPROPERTY()
	FBinaryTurn CurrentTurn;

	UPROPERTY()
	TArray<FBinaryTurnAction> PendingTurnActions;

	UPROPERTY()
	FBinaryTurnAction CurrentTurnAction;
};
