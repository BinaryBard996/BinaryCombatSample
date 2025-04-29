// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayEffectComponent/GEComponent_Attribute.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Ability/BinaryAbilityTypes.h"

bool UBinaryGameplayEffectComp_Attribute::CanGameplayEffectApply(
	const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const
{
	UAbilitySystemComponent* ASC = ActiveGEContainer.Owner;
	if(!IsValid(ASC))
	{
		return false;
	}

	for(const FBinaryAttributeCondition& Condition: RemovalAttributeConditions)
	{
		if(Condition.CanRegisterCheck(ASC))
		{
			if(Condition.CheckCondition(ASC))
			{
				return false;
			}
		}
	}

	return true;
}

bool UBinaryGameplayEffectComp_Attribute::OnActiveGameplayEffectAdded(
	FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const
{
	UAbilitySystemComponent* ASC = ActiveGEContainer.Owner;
	if(!IsValid(ASC))
	{
		return false;
	}

	TArray<TTuple<FGameplayAttribute, FDelegateHandle>> AllBounds;
	for(const FBinaryAttributeCondition& Condition: RemovalAttributeConditions)
	{
		if(Condition.CanRegisterCheck(ASC))
		{
			FDelegateHandle Handle = ASC->GetGameplayAttributeValueChangeDelegate(Condition.Attribute).AddUObject(this, &UBinaryGameplayEffectComp_Attribute::OnAttributeChanged, ActiveGE.Handle);
			AllBounds.Emplace(Condition.Attribute, Handle);
		}
	}

	bool bOngoingFlag = true;
	for(const FBinaryAttributeCondition& Condition: OngoingAttributeConditions)
	{
		if(Condition.CanRegisterCheck(ASC))
		{
			if(Condition.CheckCondition(ASC))
			{
				bOngoingFlag = false;
				FDelegateHandle Handle = ASC->GetGameplayAttributeValueChangeDelegate(Condition.Attribute).AddUObject(this, &UBinaryGameplayEffectComp_Attribute::OnAttributeChanged, ActiveGE.Handle);
				AllBounds.Emplace(Condition.Attribute, Handle);
			}
		}
	}

	ActiveGE.EventSet.OnEffectRemoved.AddUObject(this, &UBinaryGameplayEffectComp_Attribute::OnActiveGameplayEffectRemoved, ASC, MoveTemp(AllBounds));
	return !bOngoingFlag;
}

void UBinaryGameplayEffectComp_Attribute::OnActiveGameplayEffectRemoved(
	const FGameplayEffectRemovalInfo& EffectRemovalInfo, UAbilitySystemComponent* ASC, TArray<TTuple<FGameplayAttribute, FDelegateHandle>> AllBounds) const
{
	if(!IsValid(ASC))
	{
		return;
	}
	
	for(TTuple<FGameplayAttribute, FDelegateHandle> Bound: AllBounds)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Bound.Key).Remove(Bound.Value);
	}
}

void UBinaryGameplayEffectComp_Attribute::OnAttributeChanged(const FOnAttributeChangeData& AttributeChangeData,
                                                             FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	UAbilitySystemComponent* ASC = ActiveEffectHandle.GetOwningAbilitySystemComponent();
	if(!IsValid(ASC))
	{
		return;
	}
	
	bool bRemoveFlag = false;
	for(const FBinaryAttributeCondition& Condition: RemovalAttributeConditions)
	{
		if(Condition.CheckCondition(ASC, AttributeChangeData))
		{
			bRemoveFlag = true;
			break;
		}
	}

	if(bRemoveFlag)
	{
		ASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
		return;
	}

	
	bool bOngoingFlag = true;
	for(const FBinaryAttributeCondition& Condition: OngoingAttributeConditions)
	{
		if(!Condition.CheckCondition(ASC, AttributeChangeData))
		{
			bOngoingFlag = false;
			break;
		}
	}

	ASC->SetActiveGameplayEffectInhibit(MoveTemp(ActiveEffectHandle), !bOngoingFlag, true);
}
