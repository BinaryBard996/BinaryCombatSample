// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "BinaryAbilitySystemGlobals.generated.h"

struct FBinaryAbilityDataRow;
/**
 * 
 */
UCLASS(Config=Game)
class BINARYCOMBAT_API UBinaryAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	static UBinaryAbilitySystemGlobals& Get()
	{
		return *Cast<UBinaryAbilitySystemGlobals>(IGameplayAbilitiesModule::Get().GetAbilitySystemGlobals());	
	};
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	virtual void InitGlobalData() override;
	
	UDataTable* GetAbilityDataTable();
	FBinaryAbilityDataRow FindAbilityDataFromDataTable(FName RowName);

protected:
	UPROPERTY()
	TObjectPtr<UDataTable> AbilityDataTable;
};
