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

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FBinaryGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FBinaryGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

