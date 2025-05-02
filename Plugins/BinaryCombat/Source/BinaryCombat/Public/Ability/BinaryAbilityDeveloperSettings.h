// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BinaryAbilityDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Binary Gameplay Abilities Settings"))
class BINARYCOMBAT_API UBinaryAbilityDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category=Global)
	TSoftObjectPtr<UDataTable> SoftAbilityDataTable;
};
