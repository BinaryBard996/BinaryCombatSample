// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryGameplayAbility.h"

#include "AbilitySystemGlobals.h"
#include "BinaryCombatLog.h"
#include "BinaryCombatTags.h"
#include "Ability/BinaryAbilitySystemGlobals.h"
#include "Ability/BinaryAbilityTypes.h"

void UBinaryGameplayAbility::GetOwnedGameplayTags(FGameplayTagContainer& OutTagContainer) const
{
	OutTagContainer.AppendTags(GetAssetTags());
}

void UBinaryGameplayAbility::GetAllAbilityAssetTags(const FGameplayAbilitySpec& AbilitySpec,
                                                    FGameplayTagContainer& OutTagContainer)
{
	OutTagContainer = AbilitySpec.GetDynamicSpecSourceTags();
	if(const IGameplayTagAssetInterface* TagAssetInterface = Cast<IGameplayTagAssetInterface>(AbilitySpec.Ability))
	{
		TagAssetInterface->GetOwnedGameplayTags(OutTagContainer);
	}
}

void UBinaryGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

FName UBinaryGameplayAbility::GetAbilityID() const
{
	return AbilityID;
}