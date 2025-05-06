// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayAbilityTurnBasedBlueprint.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAMEPLAYABILITIES_API UGameplayAbilityTurnBasedBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void TickTurn(UAbilitySystemComponent* AbilitySystemComponent, int32 Delta = 1);
};
