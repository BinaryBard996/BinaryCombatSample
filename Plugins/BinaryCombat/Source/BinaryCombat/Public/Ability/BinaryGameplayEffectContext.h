// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "BinaryGameplayEffectContext.generated.h"

/**
 * 
 */
USTRUCT()
struct FBinaryGameplayEffectContext: public FGameplayEffectContext
{
	GENERATED_BODY()

	FBinaryGameplayEffectContext(): FGameplayEffectContext(){}
	FBinaryGameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser): FGameplayEffectContext(InInstigator, InEffectCauser){}

	static BINARYCOMBAT_API FBinaryGameplayEffectContext* ExtractEffectContext(struct FGameplayEffectContextHandle Handle);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FBinaryGameplayEffectContext::StaticStruct();
	};
};
