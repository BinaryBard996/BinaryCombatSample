// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BinaryInputConfig.h"

#include "BinaryCombatLog.h"

UBinaryInputConfig::UBinaryInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UBinaryInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag,
                                                                    bool bLogNotFound) const
{
	for(const FBinaryInputAction& InputAction: NativeInputActions)
	{
		if(InputAction.InputAction && (InputAction.InputTag == InputTag))
		{
			return InputAction.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogBinary, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
