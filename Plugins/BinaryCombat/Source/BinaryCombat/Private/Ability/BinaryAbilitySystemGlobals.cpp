// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilitySystemGlobals.h"

#include "Ability/BinaryGameplayEffectContext.h"

FGameplayEffectContext* UBinaryAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBinaryGameplayEffectContext();
}
