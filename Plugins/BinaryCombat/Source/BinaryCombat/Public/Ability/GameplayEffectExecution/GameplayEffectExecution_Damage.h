// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameplayEffectExecution_Damage.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UGameplayEffectExecution_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UGameplayEffectExecution_Damage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
