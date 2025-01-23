// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BinaryPlayerState.h"

#include "Ability/BinaryAbilitySystemComponent.h"

ABinaryPlayerState::ABinaryPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBinaryAbilitySystemComponent>(this, "AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UBinaryAbilitySystemComponent* ABinaryPlayerState::GetBinaryAbilitySystemComponent() const
{
	return Cast<UBinaryAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ABinaryPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
