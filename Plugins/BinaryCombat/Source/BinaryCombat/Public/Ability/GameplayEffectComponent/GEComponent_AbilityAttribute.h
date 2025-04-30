// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Ability/BinaryGameplayEffectComponent.h"
#include "GEComponent_AbilityAttribute.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayEffectRemovalInfo;
struct FBinaryAbilityAttributeModifer;

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryGameplayEffectComp_AbilityAttribute : public UBinaryGameplayEffectComponent
{
	GENERATED_BODY()

public:
	UBinaryGameplayEffectComp_AbilityAttribute();

	virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const override;

protected:
	void OnActiveGameplayEffectInhibitionChanged(FActiveGameplayEffectHandle EffectHandle, bool bIsInhibited) const;
	void OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo) const;

	void AddAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const;
	void RemoveAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Attribute")
	TArray<FBinaryAbilityAttributeModifer> Modifiers;
};
