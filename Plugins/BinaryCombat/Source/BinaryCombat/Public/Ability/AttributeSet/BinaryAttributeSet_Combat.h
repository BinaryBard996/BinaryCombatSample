// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Ability/BinaryAttributeSet.h"
#include "BinaryAttributeSet_Combat.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryAttributeSet_Combat : public UBinaryAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UBinaryAttributeSet_Combat, BaseDamage);


private:
	UPROPERTY(BlueprintReadOnly, Category="Binary|AttributeSet", meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BaseDamage;
};
