// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayAbilitySpecHandle.h"
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
struct BINARYCOMBAT_API FBinaryAttributeCondition
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

struct BINARYCOMBAT_API FBinaryAbilityAttributeAggregatorEvaluateParameter
{
	FGameplayTagContainer SourceTagContainer;
	FGameplayTagContainer AbilityTagContainer;
	FGameplayTagContainer EffectTagContainer;

	FGameplayAbilitySpecHandle AbilityHandle;
};

struct BINARYCOMBAT_API FBinaryAbilityAttributeMod
{
	FGameplayTagRequirements SourceTagRequirements;
	FGameplayTagRequirements AbilityTagRequirements;
	FGameplayTagRequirements EffectTagRequirements;
	FGameplayAbilitySpecHandle AbilityHandle;
	FActiveGameplayEffectHandle ActiveEffectHandle;
	
	FGameplayTag ModChannel;
	EGameplayModOp::Type Op;
	float EvaluateMagnitude;
};

struct BINARYCOMBAT_API FBinaryAbilityAttributeModContainer
{
	TArray<FBinaryAbilityAttributeMod> Mods;
};

USTRUCT()
struct BINARYCOMBAT_API FBinaryAbilityAttributeAggregator
{
	GENERATED_BODY()

	TArray<FBinaryAbilityAttributeModContainer> ModInfos[EGameplayModOp::Max];
};








