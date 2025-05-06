// Fill out your copyright notice in the Description page of Project Settings.


#include "Turnbased/GameplayAbilityTurnBasedBlueprint.h"

#include "AbilitySystemGlobals.h"

void UGameplayAbilityTurnBasedBlueprint::TickTurn(UAbilitySystemComponent* AbilitySystemComponent, int32 Delta)
{
	FAbilityTimerManager& AbilityTimerManager = UAbilitySystemGlobals::Get().GetAbilityTimerManager();
	AbilityTimerManager.TickTurn(AbilitySystemComponent, Delta);
}
