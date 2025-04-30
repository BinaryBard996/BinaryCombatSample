// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BinaryAbilityTypes.h"
#include "BinaryAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//------------------------------------------------------
	//                  Common Functions
	//------------------------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category="Ability")
	FGameplayAbilitySpecHandle GiveAbilityWithParams(const FBinaryAbilityInitParams& AbilityInitParams);

	//------------------------------------------------------
	//                 Ability Attribute
	//------------------------------------------------------
public:
	UFUNCTION(BlueprintPure, Category="Ability Attribute")
	float EvaluateAbilityAttribute(FGameplayTag AttributeTag, FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintPure, Category="Ability Attribute")
	float EvaluateAbilityAttributeWithEffectSpec(FGameplayTag AttributeTag, const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayEffectSpecHandle& EffectSpecHandle);
	
	float InternalEvaluateAbilityAttribute(const FGameplayTag& AttributeTag, const float BaseValue, const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter);
	
	void AddActiveGameplayEffectAbilityAttributeModifiers(const FActiveGameplayEffectHandle& EffectHandle, const TArray<FBinaryAbilityAttributeModifer>& Modifiers);
	void RemoveActiveGameplayEffectAbilityAttributeModifiers(const FActiveGameplayEffectHandle& EffectHandle);

protected:
	TMap<FGameplayTag, FBinaryAbilityAttributeAggregator> AbilityAttributeAggregators;

	//------------------------------------------------------
};
