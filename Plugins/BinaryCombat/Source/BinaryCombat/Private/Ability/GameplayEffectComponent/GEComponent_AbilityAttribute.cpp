// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayEffectComponent/GEComponent_AbilityAttribute.h"

#include "BinaryCombatLog.h"
#include "GameplayEffect.h"
#include "Ability/BinaryAbilitySystemComponent.h"

UBinaryGameplayEffectComp_AbilityAttribute::UBinaryGameplayEffectComp_AbilityAttribute()
{
#if WITH_EDITORONLY_DATA
	EditorFriendlyName = TEXT("Modify Ability Attribute While Active.");
#endif
}

bool UBinaryGameplayEffectComp_AbilityAttribute::OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer,
	FActiveGameplayEffect& ActiveGE) const
{
	ActiveGE.EventSet.OnInhibitionChanged.AddUObject(this, &UBinaryGameplayEffectComp_AbilityAttribute::OnActiveGameplayEffectInhibitionChanged);
	ActiveGE.EventSet.OnEffectRemoved.AddUObject(this, &UBinaryGameplayEffectComp_AbilityAttribute::OnActiveGameplayEffectRemoved);
	return true;
}

void UBinaryGameplayEffectComp_AbilityAttribute::OnActiveGameplayEffectInhibitionChanged(FActiveGameplayEffectHandle EffectHandle,
	bool bIsInhibited) const
{
	if(!bIsInhibited)
	{
		AddAbilityAttributeModifiers(EffectHandle);
	}
	else
	{
		RemoveAbilityAttributeModifiers(EffectHandle);
	}
}

void UBinaryGameplayEffectComp_AbilityAttribute::OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo) const
{
	if(!RemovalInfo.ActiveEffect)
	{
		return;
	}
	
	RemoveAbilityAttributeModifiers(RemovalInfo.ActiveEffect->Handle);
}

void UBinaryGameplayEffectComp_AbilityAttribute::AddAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const
{
	UBinaryAbilitySystemComponent* AbilitySystemComponent = Cast<UBinaryAbilitySystemComponent>(EffectHandle.GetOwningAbilitySystemComponent());
	if(!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->AddActiveGameplayEffectAbilityAttributeModifiers(EffectHandle, Modifiers);
}

void UBinaryGameplayEffectComp_AbilityAttribute::RemoveAbilityAttributeModifiers(FActiveGameplayEffectHandle EffectHandle) const
{
	UBinaryAbilitySystemComponent* AbilitySystemComponent = Cast<UBinaryAbilitySystemComponent>(EffectHandle.GetOwningAbilitySystemComponent());
	if(!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->RemoveActiveGameplayEffectAbilityAttributeModifiers(EffectHandle);
}
