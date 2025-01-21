// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayEffectComponent/BinaryGameplayEffectComp_Attribute.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Ability/BinaryAbilityTypes.h"

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
			if(Condition.CheckCondition(ASC))
			{
				return false;
			}
			
			FDelegateHandle Handle = ASC->GetGameplayAttributeValueChangeDelegate(Condition.Attribute).AddUObject(this, &UBinaryGameplayEffectComp_Attribute::OnAttributeChanged, ActiveGE.Handle);
			AllBounds.Emplace(Condition.Attribute, Handle);
		}

	}

	ActiveGE.EventSet.OnEffectRemoved.AddUObject(this, &UBinaryGameplayEffectComp_Attribute::OnActiveGameplayEffectRemoved, ASC, MoveTemp(AllBounds));
	return true;
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
	}
}
