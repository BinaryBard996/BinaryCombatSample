// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BinaryCharacterWithAbilities.h"

#include "Ability/BinaryAbilitySystemComponent.h"

ABinaryCharacterWithAbilities::ABinaryCharacterWithAbilities(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UBinaryAbilitySystemComponent>(TEXT("Ability System Component"));
}

UBinaryAbilitySystemComponent* ABinaryCharacterWithAbilities::GetBinaryAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySystemComponent* ABinaryCharacterWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}