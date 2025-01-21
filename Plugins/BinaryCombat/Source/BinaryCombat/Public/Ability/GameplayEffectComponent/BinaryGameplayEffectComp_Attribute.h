// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "Ability/BinaryGameplayEffectComponent.h"
#include "BinaryGameplayEffectComp_Attribute.generated.h"

struct FBinaryAttributeCondition;

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryGameplayEffectComp_Attribute : public UBinaryGameplayEffectComponent
{
	GENERATED_BODY()

public:
	virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const override;
	virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const override;

protected:
	void OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& EffectRemovalInfo, UAbilitySystemComponent* ASC, TArray<TTuple<FGameplayAttribute, FDelegateHandle>> AllBounds) const;
	void OnAttributeChanged(const FOnAttributeChangeData& AttributeChangeData, FActiveGameplayEffectHandle ActiveEffectHandle) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute Condition")
	TArray<FBinaryAttributeCondition> RemovalAttributeConditions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute Condition")
	TArray<FBinaryAttributeCondition> OngoingAttributeConditions;
};
