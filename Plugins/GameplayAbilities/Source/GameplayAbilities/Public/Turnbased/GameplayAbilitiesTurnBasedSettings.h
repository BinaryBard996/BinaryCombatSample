// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "UObject/Object.h"
#include "GameplayAbilitiesTurnBasedSettings.generated.h"

GAMEPLAYABILITIES_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Type_TurnBased);

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Gameplay Abilities Turn Based Settings"))
class GAMEPLAYABILITIES_API UGameplayAbilitiesTurnBasedSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))
	FGameplayTag GameplayEffectTurnBasedTag = Effect_Type_TurnBased;
};
