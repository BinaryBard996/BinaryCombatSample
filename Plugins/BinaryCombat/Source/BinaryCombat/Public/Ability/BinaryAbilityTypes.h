// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "BinaryAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class EBinaryAttributeConditionType: uint8
{
	Equal			UMETA(DisplayName="=="), 
	Less			UMETA(DisplayName="<"),
	LessOrEqual		UMETA(DisplayName="<="),
	Greater			UMETA(DisplayName=">"),
	GreaterOrEqual	UMETA(DisplayName=">="),
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

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EBinaryAttributeConditionType Condition = EBinaryAttributeConditionType::LessOrEqual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Value = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bPercent = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bPercent", EditConditionHides))
	FGameplayAttribute BackAttribute;

	bool CanRegisterCheck(const UAbilitySystemComponent* ASC) const;

	bool CheckCondition(const UAbilitySystemComponent* ASC) const;
	bool CheckCondition(const UAbilitySystemComponent* ASC, const FOnAttributeChangeData& AttributeChangeData) const;

protected:
	bool Check(const float CheckValue) const;
};
