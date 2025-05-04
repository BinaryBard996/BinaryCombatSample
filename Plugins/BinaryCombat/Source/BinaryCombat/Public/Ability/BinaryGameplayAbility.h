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

	static void GetAllAbilityAssetTags(const FGameplayAbilitySpec& AbilitySpec, FGameplayTagContainer& OutTagContainer);

protected:
	// ~GameplayAbility START
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	// GameplayAbility END

	virtual void InitGameplayAbilityData(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Ability")
	FName AbilityID;
};
