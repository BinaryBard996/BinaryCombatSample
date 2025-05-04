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

	InitGameplayAbilityData(ActorInfo, Spec);
}

void UBinaryGameplayAbility::InitGameplayAbilityData(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	UBinaryAbilitySystemGlobals& AbilitySystemGlobals = UBinaryAbilitySystemGlobals::Get();
	const UDataTable* DataTable = AbilitySystemGlobals.GetAbilityDataTable();
	if(!DataTable)
	{
		return;
	}

	FBinaryAbilityDataRow* Data = DataTable->FindRow<FBinaryAbilityDataRow>(AbilityID, "", false);
	if(!Data)
	{
		return;
	}

	const int32 AbilityLevel = GetAbilityLevel();
	if(!Data->LevelData.IsValidIndex(AbilityLevel))
	{
		UE_LOG(LogBinaryAbilitySystem, Error, TEXT("Novalid ability level data for ability: %s, ability id: %s."), *GetClass()->GetName(), *AbilityID.ToString());
		return;
	}

	const float AbilityDamageRate = Data->LevelData[AbilityLevel].AbilityDamageRate;
	GetCurrentAbilitySpec()->SetByCallerTagMagnitudes.Add(BinaryCombatTags::Ability_Attribute_DamageRate, AbilityDamageRate);
}
