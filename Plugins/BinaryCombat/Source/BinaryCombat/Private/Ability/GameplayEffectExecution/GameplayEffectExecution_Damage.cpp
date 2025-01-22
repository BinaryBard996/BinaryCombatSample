// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayEffectExecution/GameplayEffectExecution_Damage.h"

#include "Ability/BinaryAbilitySystemComponent.h"
#include "Ability/AttributeSet/BinaryAttributeSet_Combat.h"

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

void UGameplayEffectExecution_Damage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UBinaryAbilitySystemComponent* SourceASC = Cast<UBinaryAbilitySystemComponent>(ExecutionParams.GetSourceAbilitySystemComponent());
	UBinaryAbilitySystemComponent* TargetASC = Cast<UBinaryAbilitySystemComponent>(ExecutionParams.GetTargetAbilitySystemComponent());
	if(!SourceASC || !TargetASC) return;
}
