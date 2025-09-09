// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BinaryGameInstance.h"

#include "Ability/BinaryAbilitySystemGlobals.h"

void UBinaryGameInstance::Init()
{
	Super::Init();

	UBinaryAbilitySystemGlobals& AbilitySystemGlobals = UBinaryAbilitySystemGlobals::Get();
	AbilitySystemGlobals.InitAbilitySystemData();
}
