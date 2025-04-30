// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryGameplayEffectContext.h"

FBinaryGameplayEffectContext* FBinaryGameplayEffectContext::ExtractEffectContext(FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if(BaseEffectContext != nullptr && BaseEffectContext->GetScriptStruct()->IsChildOf(FBinaryGameplayEffectContext::StaticStruct()))
	{
		return static_cast<FBinaryGameplayEffectContext*>(BaseEffectContext);
	}
	return nullptr;
}