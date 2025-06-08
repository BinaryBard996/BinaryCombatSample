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
	UFUNCTION(BlueprintCallable)
	void ClearTurnSystem();

	UFUNCTION(BlueprintCallable)
	void AddTurnPawn(APawn* TurnPawn);

	UFUNCTION(BlueprintCallable)
	void RemoveTurnPawn(APawn* TurnPawn);

	UFUNCTION(BlueprintCallable)
	void ProcessNewTurn();

	UFUNCTION(BlueprintCallable)
	FBinaryTurnAction GetCurrentTurnAction() const;

	void GenerateTurnActionQueue();

protected:
	UPROPERTY()
	TArray<FBinaryTurnAction> TurnActions;
	
	UPROPERTY()
	TArray<FBinaryTurnItem> TurnItems;

	UPROPERTY()
	FBinaryTurnAction CurrentTurnAction;
};
