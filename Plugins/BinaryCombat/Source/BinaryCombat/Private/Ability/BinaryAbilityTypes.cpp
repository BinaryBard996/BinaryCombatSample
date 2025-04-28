// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilityTypes.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "Kismet/KismetMathLibrary.h"

bool FBinaryAttributeCondition::CanRegisterCheck(const UAbilitySystemComponent* ASC) const
{
	if(!IsValid(ASC))
	{
		return false;
	}

	if(!Attribute.IsValid() || !ASC->HasAttributeSetForAttribute(Attribute))
	{
		return false;
	}

	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
	}

	return true;
}

bool FBinaryAttributeCondition::CheckCondition(const UAbilitySystemComponent* ASC) const
{
	if(!IsValid(ASC))
	{
		return false;
	}

	float CheckValue = ASC->GetNumericAttribute(Attribute);
	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
		
		float BackAttributeValue = ASC->GetNumericAttribute(BackAttribute);
		CheckValue = UKismetMathLibrary::SafeDivide(CheckValue, BackAttributeValue);
	}

	return Check(CheckValue);
}

bool FBinaryAttributeCondition::CheckCondition(const UAbilitySystemComponent* ASC, const FOnAttributeChangeData& AttributeChangeData) const
{
	if(AttributeChangeData.Attribute != Attribute or !IsValid(ASC))
	{
		return false;
	}

	float CheckValue = AttributeChangeData.NewValue;
	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
		
		float BackAttributeValue = ASC->GetNumericAttribute(BackAttribute);
		CheckValue = UKismetMathLibrary::SafeDivide(CheckValue, BackAttributeValue);
	}
	
	return Check(CheckValue);
}

bool FBinaryAttributeCondition::Check(const float CheckValue) const
{
	switch(Condition)
	{
	case EBinaryAttributeConditionType::Equal:
		{
			if(CheckValue == Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::Less:
		{
			if(CheckValue < Value) return true;
		}
	case EBinaryAttributeConditionType::LessOrEqual:
		{
			if(CheckValue <= Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::Greater:
		{
			if(CheckValue > Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::GreaterOrEqual:
		{
			if(CheckValue >= Value) return true;
		}
	}

	return false;
}

void FBinaryAbilityAttributeMod::UpdateQualifies(
	const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter) const
{
	bool bSourceMet = SourceTagRequirements.IsEmpty() || SourceTagRequirements.RequirementsMet(EvaluateParameter.SourceTagContainer);
	bool bTargetMet = TargetTagRequirements.IsEmpty() || TargetTagRequirements.RequirementsMet(EvaluateParameter.TargetTagContainer);
	bool bAbilityMet = AbilityTagRequirements.IsEmpty() || AbilityTagRequirements.RequirementsMet(EvaluateParameter.AbilityTagContainer);
	bool bEffectMet = EffectTagRequirements.IsEmpty() || EffectTagRequirements.RequirementsMet(EvaluateParameter.EffectTagContainer);

	bQualified = bSourceMet && bTargetMet && bAbilityMet && bEffectMet;
}

void FBinaryAbilityAttributeAggregator::AddAggregatorMod(float EvaluatedMagnitude, TEnumAsByte<EGameplayModOp::Type> ModOp,
                                               const FGameplayTagRequirements& SourceTagRequirements, const FGameplayTagRequirements& TargetTagRequirements,
                                               const FGameplayTagRequirements& AbilityTagRequirements, const FGameplayTagRequirements& EffectTagRequirements,
                                               const FActiveGameplayEffectHandle& ActiveHandle)
{
	TArray<FBinaryAbilityAttributeMod>& ModList = ModInfos[ModOp];

	int32 NewIndex = ModList.AddUninitialized();
	FBinaryAbilityAttributeMod& NewMod = ModList[NewIndex];

	NewMod.SourceTagRequirements = SourceTagRequirements;
	NewMod.TargetTagRequirements = TargetTagRequirements;
	NewMod.AbilityTagRequirements = AbilityTagRequirements;
	NewMod.EffectTagRequirements = EffectTagRequirements;
	NewMod.ActiveEffectHandle = ActiveHandle;
	NewMod.EvaluatedMagnitude = EvaluatedMagnitude;
}

void FBinaryAbilityAttributeAggregator::RemoveAggregatorMod(const FActiveGameplayEffectHandle& Handle)
{
	for(int32 ModOpIdx = 0; ModOpIdx < UE_ARRAY_COUNT(ModInfos); ++ModOpIdx)
	{
		ModInfos[ModOpIdx].RemoveAllSwap([&Handle](const FBinaryAbilityAttributeMod& Element)
		{
			return (Element.ActiveEffectHandle == Handle);
		},
		EAllowShrinking::No);
	}
}

float FBinaryAbilityAttributeAggregator::Evaluate(float InBaseValue,
                                                          const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter) const
{
	
	
	for(const auto& Mod: ModInfos[EGameplayModOp::Override])
	{
		if(Mod.Qualifies())
		{
			return Mod.EvaluatedMagnitude;
		}
	}

	float AddBase = SumMods(ModInfos[EGameplayModOp::AddBase], GameplayEffectUtilities::GetModifierBiasByModifierOp(EGameplayModOp::AddBase), EvaluateParameter);
	float MultiplyAdditive = SumMods(ModInfos[EGameplayModOp::MultiplyAdditive], GameplayEffectUtilities::GetModifierBiasByModifierOp(EGameplayModOp::MultiplyAdditive), EvaluateParameter);
	float DivideAdditive = SumMods(ModInfos[EGameplayModOp::DivideAdditive], GameplayEffectUtilities::GetModifierBiasByModifierOp(EGameplayModOp::DivideAdditive), EvaluateParameter);
	float AddFinal = SumMods(ModInfos[EGameplayModOp::AddFinal], GameplayEffectUtilities::GetModifierBiasByModifierOp(EGameplayModOp::AddFinal), EvaluateParameter);
	float MultiplyCompound = ProductMods(ModInfos[EGameplayModOp::MultiplyCompound], EvaluateParameter);

	if (FMath::IsNearlyZero(DivideAdditive))
	{
		ABILITY_LOG(Warning, TEXT("Division summation was 0.0f in FAggregatorModChannel."));
		DivideAdditive = 1.f;
	}

	return ((InBaseValue + AddBase) * MultiplyAdditive / DivideAdditive) * MultiplyCompound + AddFinal;
}

float FBinaryAbilityAttributeAggregator::SumMods(const TArray<FBinaryAbilityAttributeMod>& InMods, float Bias,
	const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter)
{
	float Sum = Bias;

	for(const FBinaryAbilityAttributeMod& Mod: InMods)
	{
		if(Mod.Qualifies())
		{
			Sum += (Mod.EvaluatedMagnitude - Bias);
		}
	}

	return Sum;
}

float FBinaryAbilityAttributeAggregator::ProductMods(const TArray<FBinaryAbilityAttributeMod>& InMods,
	const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter)
{
	float Result = 1.f;
	for (const FBinaryAbilityAttributeMod& Mod : InMods)
	{
		if (Mod.Qualifies())
		{
			Result *= (1.f + Mod.EvaluatedMagnitude);
		}
	}

	return Result;
}

float FBinaryAbilityAttributeAggregator::MultiplyMods(const TArray<FBinaryAbilityAttributeMod>& InMods,
	const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter)
{
	float Result = 1.f;
	for (const FBinaryAbilityAttributeMod& Mod : InMods)
	{
		if (Mod.Qualifies())
		{
			Result *= Mod.EvaluatedMagnitude;
		}
	}

	return Result;
}

























