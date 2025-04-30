// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/BinaryGameplayEffectComponent.h"
#include "GEComponent_AbilityAttribute.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayEffectRemovalInfo;
struct FBinaryAbilityAttributeModifer;

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UGEComponent_AbilityAttribute : public UBinaryGameplayEffectComponent
{
	GENERATED_BODY()

public:
	UGEComponent_AbilityAttribute();

	virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const override;

protected:
	void OnActiveGameplayEffectInhibitionChanged(FActiveGameplayEffectHandle EffectHandle, bool bIsInhibited) const;

	void AddAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const;
	void RemoveAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Attribute")
	TArray<FBinaryAbilityAttributeModifer> Modifiers;
};
