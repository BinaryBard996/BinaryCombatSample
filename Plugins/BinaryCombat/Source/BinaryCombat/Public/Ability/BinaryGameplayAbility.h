// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "BinaryGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryGameplayAbility : public UGameplayAbility, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// ~IGameplayTagAssetInterface START
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& OutTagContainer) const override;
	// IGameplayTagAssetInterface END

public:
	static void GetAllAbilityAssetTags(const FGameplayAbilitySpec& AbilitySpec, FGameplayTagContainer& OutTagContainer);

};
