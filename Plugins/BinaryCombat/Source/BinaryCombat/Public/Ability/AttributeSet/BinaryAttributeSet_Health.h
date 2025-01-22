// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/BinaryAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BinaryAttributeSet_Health.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryAttributeSet_Health : public UBinaryAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UBinaryAttributeSet_Health, Health);
	ATTRIBUTE_ACCESSORS(UBinaryAttributeSet_Health, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBinaryAttributeSet_Health, Damage);

protected:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const; 

private:
	UPROPERTY(BlueprintReadOnly, Category="Binary|AttributeSet", meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category="Binary|AttributeSet", meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category="Binary|AttributeSet", meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
};
