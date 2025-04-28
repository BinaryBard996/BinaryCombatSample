// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BinaryAbilityTypes.h"
#include "BinaryAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//------------------------------------------------------
	//                  Common Functions
	//------------------------------------------------------

	//------------------------------------------------------
	//                 Ability Magnitudes
	//------------------------------------------------------
public:


protected:
	TMap<FGameplayTag, FBinaryAbilityAttributeAggregator> CommonAbilityAttributeAggregators;

	//------------------------------------------------------
};
