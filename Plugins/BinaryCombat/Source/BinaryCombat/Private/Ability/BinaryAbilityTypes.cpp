// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilityTypes.h"

bool FBinaryAttributeCondition::CheckCondition(const FOnAttributeChangeData& AttributeChangeData) const
{
	if(AttributeChangeData.Attribute == Attribute)
	{
		return false;
	}

	switch(Condition)
	{
	case EBinaryAttributeConditionType::LessOrEqual:
		{
			if(AttributeChangeData.NewValue <= Value)
			{
				return true;
			}
			break;
		}
	}

	return false;
}
