// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryGameplayAbility.h"

void UBinaryGameplayAbility::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(TagContainer);
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
