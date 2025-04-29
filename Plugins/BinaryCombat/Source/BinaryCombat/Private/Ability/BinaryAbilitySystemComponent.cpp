// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilitySystemComponent.h"

#include "BinaryCombatLog.h"
#include "Ability/BinaryGameplayAbility.h"

FGameplayAbilitySpecHandle UBinaryAbilitySystemComponent::GiveAbilityWithParams(
	const FBinaryAbilityInitParams& AbilityInitParams)
{
	if(!IsValid(AbilityInitParams.AbilityClass))
	{
		UE_LOG(LogBinaryAbilitySystem, Error, TEXT("UBinaryAbilitySystemComponent::GiveAbilityWithParams failed, AbilityClass is not valid!"));
		return FGameplayAbilitySpecHandle();
	}

	FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(AbilityInitParams.AbilityClass, 1.0, -1);
	for(const auto& AbilityAttribute: AbilityInitParams.AbilityAttributes)
	{
		AbilitySpec.SetByCallerTagMagnitudes.Add(AbilityAttribute.DataTag, AbilityAttribute.DataValue);
	}
	return GiveAbility(AbilitySpec);
}
