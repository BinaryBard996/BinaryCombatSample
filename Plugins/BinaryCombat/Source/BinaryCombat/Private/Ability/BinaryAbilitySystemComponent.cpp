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

float UBinaryAbilitySystemComponent::EvaluateAbilityAttribute(FGameplayTag AttributeTag,
                                                              FGameplayAbilitySpecHandle AbilityHandle)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityHandle);
	if(!AbilitySpec)
	{
		UE_LOG(LogBinaryAbilitySystem, Error, TEXT("UBinaryAbilitySystemComponent::EvaluateAbilityAttribute-Input ability handle is not valid! AbilityHandle: %s"), *AbilityHandle.ToString())
		return 0.f;
	}

	return InternalEvaluateAbilityAttribute(AttributeTag, AbilitySpec, nullptr);
}

float UBinaryAbilitySystemComponent::EvaluateAbilityAttributeWithEffectSpec(FGameplayTag AttributeTag,
	const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayEffectSpecHandle& EffectSpecHandle)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityHandle);
	if(!AbilitySpec)
	{
		UE_LOG(LogBinaryAbilitySystem, Error, TEXT("UBinaryAbilitySystemComponent::EvaluateAbilityAttribute-Input ability handle is not valid! AbilityHandle: %s"), *AbilityHandle.ToString())
		return 0.f;
	}

	if(!EffectSpecHandle.IsValid())
	{
		UE_LOG(LogBinaryAbilitySystem, Error, TEXT("UBinaryAbilitySystemComponent::EvaluateAbilityAttribute-Input effect handle is not valid! Ability: %s"), *AbilitySpec->Ability.GetName())
		return 0.f;
	}
	
	return InternalEvaluateAbilityAttribute(AttributeTag, AbilitySpec, EffectSpecHandle.Data.Get());
}

float UBinaryAbilitySystemComponent::InternalEvaluateAbilityAttribute(FGameplayTag AttributeTag,
	const FGameplayAbilitySpec* AbilitySpec, const FGameplayEffectSpec* EffectSpec)
{
	FBinaryAbilityAttributeEvaluateParameter EvaluateParameter;
	EvaluateParameter.SourceTagContainer = GetOwnedGameplayTags();
	if(AbilitySpec)
	{
		UBinaryGameplayAbility::GetAllAbilityAssetTags(*AbilitySpec, EvaluateParameter.AbilityTagContainer);
	}
	if(EffectSpec)
	{
		EffectSpec->GetAllAssetTags(EvaluateParameter.EffectTagContainer);
	}

	return InternalEvaluateAbilityAttribute(AttributeTag, AbilitySpec->SetByCallerTagMagnitudes.FindRef(AttributeTag), EvaluateParameter);
}

float UBinaryAbilitySystemComponent::InternalEvaluateAbilityAttribute(
	const FGameplayTag& AttributeTag, const float BaseValue, 
	const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter)
{
	float EvaluatedMagnitude = BaseValue;
	
	if(const FBinaryAbilityAttributeAggregator* Aggregator = AbilityAttributeAggregators.Find(AttributeTag))
	{
		EvaluatedMagnitude = Aggregator->Evaluate(EvaluatedMagnitude, EvaluateParameter);
	}

	return EvaluatedMagnitude;
}

void UBinaryAbilitySystemComponent::AddActiveGameplayEffectAbilityAttributeModifiers(
	const FActiveGameplayEffectHandle& EffectHandle, const TArray<FBinaryAbilityAttributeModifer>& Modifiers)
{
	if(!EffectHandle.IsValid())
	{
		return;
	}

	const FActiveGameplayEffect* Effect = GetActiveGameplayEffect(EffectHandle);
	if(!Effect)
	{
		return;
	}
	
	for(const FBinaryAbilityAttributeModifer& Modifier: Modifiers)
	{
		if(!Modifier.AbilityAttributeTag.IsValid())
		{
			continue;
		}

		float EvaluateMagnitude = 0.f;
		Modifier.ModifierMagnitude.AttemptCalculateMagnitude(Effect->Spec, EvaluateMagnitude);
		AbilityAttributeAggregators.FindOrAdd(Modifier.AbilityAttributeTag).
			AddAggregatorMod(EvaluateMagnitude, Modifier.ModifierOp, &Modifier.SourceTagRequirements, &Modifier.AbilityTagRequirements, &Modifier.EffectTagRequirements, EffectHandle);
	}
}

void UBinaryAbilitySystemComponent::RemoveActiveGameplayEffectAbilityAttributeModifiers(
	const FActiveGameplayEffectHandle& EffectHandle)
{
	if(!EffectHandle.IsValid())
	{
		return;
	}
	
	for(auto& Pair: AbilityAttributeAggregators)
	{
		Pair.Value.RemoveAggregatorMod(EffectHandle);
	}
}














