// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "BinaryAbilityTypes.generated.h"

class UBinaryGameplayAbility;

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

struct BINARYCOMBAT_API FBinaryAbilityAttributeEvaluateParameter
{
	FGameplayTagContainer SourceTagContainer;
	FGameplayTagContainer AbilityTagContainer;
	FGameplayTagContainer EffectTagContainer;
};

struct BINARYCOMBAT_API FBinaryAbilityAttributeMod
{
	const FGameplayTagRequirements* SourceTagRequirements;
	const FGameplayTagRequirements* AbilityTagRequirements;
	const FGameplayTagRequirements* EffectTagRequirements;
	FActiveGameplayEffectHandle ActiveEffectHandle;
	
	float EvaluatedMagnitude;

	FBinaryAbilityAttributeMod();
	bool Qualifies() const { return bQualified; }
	void UpdateQualifies(const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter) const;
	
private:
	mutable bool bQualified = true;
};

struct BINARYCOMBAT_API FBinaryAbilityAttributeAggregator
{

public:
	void AddAggregatorMod(float EvaluatedMagnitude, TEnumAsByte<EGameplayModOp::Type> ModOp, const FGameplayTagRequirements* SourceTagRequirements, const FGameplayTagRequirements* AbilityTagRequirements, const FGameplayTagRequirements* EffectTagRequirements, const FActiveGameplayEffectHandle& ActiveHandle);
	void RemoveAggregatorMod(const FActiveGameplayEffectHandle& Handle);
	
	float Evaluate(float InBaseValue, const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter) const;
	void EvaluateQualificationForAllMods(const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter) const;
	
	static float SumMods(const TArray<FBinaryAbilityAttributeMod>& InMods, float Bias, const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter);
	static float ProductMods(const TArray<FBinaryAbilityAttributeMod>& InMods, const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter);
	static float MultiplyMods(const TArray<FBinaryAbilityAttributeMod>& InMods, const FBinaryAbilityAttributeEvaluateParameter& EvaluateParameter);
	
private:
	TArray<FBinaryAbilityAttributeMod> ModInfos[EGameplayModOp::Max];
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryAbilityAttributeModifer
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories="Ability.Attribute"))
	FGameplayTag AbilityAttributeTag;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EGameplayModOp::Type> ModifierOp = EGameplayModOp::AddBase;

	UPROPERTY(EditDefaultsOnly)
	FGameplayEffectModifierMagnitude ModifierMagnitude;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagRequirements SourceTagRequirements;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagRequirements AbilityTagRequirements;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagRequirements EffectTagRequirements;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryAbilityAttributeDefine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Ability.Attribute"))
	FGameplayTag DataTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DataValue = 0.f;
};

// 临时参数，后续使用DT管理技能参数
USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryAbilityInitParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBinaryGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBinaryAbilityAttributeDefine> AbilityAttributes;
};

// 技能属性
USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryAbilityDataLevel
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AbilityDamageRate = 1.f;
	
};

// 定义技能的属性
USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryAbilityData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FBinaryAbilityDataLevel> DataByLevel;
};





