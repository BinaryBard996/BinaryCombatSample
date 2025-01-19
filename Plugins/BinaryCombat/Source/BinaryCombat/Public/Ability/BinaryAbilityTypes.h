// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "BinaryAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class EBinaryAttributeConditionType: uint8
{
	LessOrEqual,
};

USTRUCT(BlueprintType)
struct FBinaryAbilityTaskConfig
{
	GENERATED_BODY()
	
};

// 判断属性是否满足条件
USTRUCT(BlueprintType)
struct FBinaryAttributeCondition
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBinaryAttributeConditionType Condition = EBinaryAttributeConditionType::LessOrEqual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Value = 0.f;

	bool CheckCondition(const FOnAttributeChangeData& AttributeChangeData) const;
};
