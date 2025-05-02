// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryGameplayAbility.h"

#include "AbilitySystemGlobals.h"
#include "Ability/BinaryAbilitySystemGlobals.h"

void UBinaryGameplayAbility::GetOwnedGameplayTags(FGameplayTagContainer& OutTagContainer) const
{
	OutTagContainer.AppendTags(GetAssetTags());
}

void UBinaryGameplayAbility::GetAllAbilityAssetTags(const FGameplayAbilitySpec& AbilitySpec,
                                                    FGameplayTagContainer& OutTagContainer)
{
	OutTagContainer = AbilitySpec.GetDynamicSpecSourceTags();
	if(IGameplayTagAssetInterface* TagAssetInterface = Cast<IGameplayTagAssetInterface>(AbilitySpec.Ability))
	{
		TagAssetInterface->GetOwnedGameplayTags(OutTagContainer);
	}
}

void UBinaryGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	UBinaryAbilitySystemGlobals& AbilitySystemGlobals = UBinaryAbilitySystemGlobals::Get();
	AbilitySystemGlobals.GetAbilityDataTable()->FindRow<>()
}
