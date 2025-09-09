// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilitySystemGlobals.h"

#include "Ability/BinaryAbilityDeveloperSettings.h"
#include "Ability/BinaryAbilityTypes.h"
#include "Ability/BinaryGameplayEffectContext.h"

FGameplayEffectContext* UBinaryAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBinaryGameplayEffectContext();
}

void UBinaryAbilitySystemGlobals::InitAbilitySystemData()
{
	const UBinaryAbilityDeveloperSettings* BinaryAbilityDeveloperSettings = GetDefault<UBinaryAbilityDeveloperSettings>();
	if(BinaryAbilityDeveloperSettings->SoftAbilityDataTable.IsValid())
	{
		AbilityDataTable = Cast<UDataTable>(BinaryAbilityDeveloperSettings->SoftAbilityDataTable.TryLoad());
	}
}

UDataTable* UBinaryAbilitySystemGlobals::GetAbilityDataTable()
{
	if(!AbilityDataTable)
	{
		const UBinaryAbilityDeveloperSettings* BinaryAbilityDeveloperSettings = GetDefault<UBinaryAbilityDeveloperSettings>();
		if(BinaryAbilityDeveloperSettings->SoftAbilityDataTable.IsValid())
		{
			AbilityDataTable = Cast<UDataTable>(BinaryAbilityDeveloperSettings->SoftAbilityDataTable.TryLoad());
		}
	}

	return AbilityDataTable;
}

FBinaryAbilityDataRow UBinaryAbilitySystemGlobals::FindAbilityDataFromDataTable(FName RowName)
{
	if(UDataTable* DataTable = GetAbilityDataTable())
	{
		if(FBinaryAbilityDataRow* DataRow = DataTable->FindRow<FBinaryAbilityDataRow>(RowName, "", false))
		{
			return *DataRow;
		}
	}

	
	return FBinaryAbilityDataRow();
}
