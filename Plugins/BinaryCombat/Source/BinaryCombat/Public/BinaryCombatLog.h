// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

BINARYCOMBAT_API DECLARE_LOG_CATEGORY_EXTERN(LogBinary, Log, All);
BINARYCOMBAT_API DECLARE_LOG_CATEGORY_EXTERN(LogBinaryTeams, Log, All);
BINARYCOMBAT_API DECLARE_LOG_CATEGORY_EXTERN(LogBinaryAbilitySystem, Log, All);

BINARYCOMBAT_API FString GetClientServerContextString(UObject* ContextObject);
