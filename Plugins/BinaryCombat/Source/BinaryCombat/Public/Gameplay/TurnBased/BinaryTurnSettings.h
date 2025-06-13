// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowAsset.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "BinaryTurnSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Binary Turn Settings"))
class BINARYCOMBAT_API UBinaryTurnSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBinaryTurnSettings();
	
	UPROPERTY(Config, EditDefaultsOnly, Category=BinaryTurn, meta=(GameplayTagFilter="Turn.Action"))
	TMap<FGameplayTag, TSoftObjectPtr<UFlowAsset>> TurnFlowAssets;
};
