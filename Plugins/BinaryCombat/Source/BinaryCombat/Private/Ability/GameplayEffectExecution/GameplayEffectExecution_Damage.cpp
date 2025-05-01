// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayEffectExecution/GameplayEffectExecution_Damage.h"

#include <rapidjson/schema.h>

#include "BinaryCombatTags.h"
#include "Ability/BinaryAbilitySystemComponent.h"
#include "Ability/BinaryGameplayAbility.h"
#include "Ability/BinaryGameplayEffectContext.h"
#include "Ability/AttributeSet/BinaryAttributeSet_Combat.h"
#include "Ability/AttributeSet/BinaryAttributeSet_Health.h"

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition BaseDamageDef;

	FDamageStatics()
	{
		BaseDamageDef = FGameplayEffectAttributeCaptureDefinition(UBinaryAttributeSet_Combat::GetBaseDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
	}
};

static FDamageStatics& DamageStatics()
{
	static FDamageStatics Statics;
	return Statics;
}

UGameplayEffectExecution_Damage::UGameplayEffectExecution_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().BaseDamageDef);
}

void UGameplayEffectExecution_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FBinaryGameplayEffectContext* TypedContext = FBinaryGameplayEffectContext::ExtractEffectContext(Spec.GetContext());
	check(TypedContext)

	UBinaryAbilitySystemComponent* SourceASC = Cast<UBinaryAbilitySystemComponent>(ExecutionParams.GetSourceAbilitySystemComponent());
	UBinaryAbilitySystemComponent* TargetASC = Cast<UBinaryAbilitySystemComponent>(ExecutionParams.GetTargetAbilitySystemComponent());
	if(!SourceASC || !TargetASC) return;

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EffectEvaluateParameters;
	EffectEvaluateParameters.SourceTags = SourceTags;
	EffectEvaluateParameters.TargetTags = TargetTags;

	float BaseDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaseDamageDef, EffectEvaluateParameters, BaseDamage);
	
	// 获取伤害系数 start
	float DamageRate = 1.f;
	
	bool bAbilityDamageRateReady = false;
	if(const UBinaryGameplayAbility* AbilityInstance = Cast<UBinaryGameplayAbility>(TypedContext->GetAbilityInstance_NotReplicated()))
	{
		if(FGameplayAbilitySpec* AbilitySpec = SourceASC->FindAbilitySpecFromHandle(AbilityInstance->GetCurrentAbilitySpecHandle()))
		{
			FBinaryAbilityAttributeEvaluateParameter AbilityAttributeEvaluateParameter;
			AbilityAttributeEvaluateParameter.SourceTagContainer = *SourceTags;
			Spec.GetAllAssetTags(AbilityAttributeEvaluateParameter.EffectTagContainer);
			UBinaryGameplayAbility::GetAllAbilityAssetTags(*AbilitySpec, AbilityAttributeEvaluateParameter.AbilityTagContainer);
			DamageRate = SourceASC->InternalEvaluateAbilityAttribute(BinaryCombatTags::Ability_Attribute_DamageRate, AbilitySpec, &Spec);
			bAbilityDamageRateReady = true;
		}
	}

	if(!bAbilityDamageRateReady)
	{
		DamageRate = Spec.GetSetByCallerMagnitude(BinaryCombatTags::Ability_Attribute_DamageRate, false, 1.f);
	}
	// 获取伤害系数 end

	float FinalDamage = BaseDamage * DamageRate;
	FinalDamage = FMath::Floor(FMath::Max(0.0, FinalDamage));

	if(FinalDamage)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UBinaryAttributeSet_Health::GetDamageAttribute(), EGameplayModOp::Override, FinalDamage));
	}
}
