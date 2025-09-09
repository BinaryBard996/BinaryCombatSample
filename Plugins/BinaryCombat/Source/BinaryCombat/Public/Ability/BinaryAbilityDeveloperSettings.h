// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BinaryAbilityDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Binary Gameplay Abilities Settings"), MinimalAPI)
class UBinaryAbilityDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category=Global, meta=(DisplayName = "Global Curve Table", AllowedClasses="/Script/Engine.DataTable", ConfigRestartRequired=true))
	FSoftObjectPath SoftAbilityDataTable;
};
