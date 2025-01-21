// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BinaryAbilityTypes.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

bool FBinaryAttributeCondition::CanRegisterCheck(const UAbilitySystemComponent* ASC) const
{
	if(!IsValid(ASC))
	{
		return false;
	}

	if(!Attribute.IsValid() || !ASC->HasAttributeSetForAttribute(Attribute))
	{
		return false;
	}

	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
	}

	return true;
}

bool FBinaryAttributeCondition::CheckCondition(const UAbilitySystemComponent* ASC) const
{
	if(!IsValid(ASC))
	{
		return false;
	}

	float CheckValue = ASC->GetNumericAttribute(Attribute);
	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
		
		float BackAttributeValue = ASC->GetNumericAttribute(BackAttribute);
		CheckValue = UKismetMathLibrary::SafeDivide(CheckValue, BackAttributeValue);
	}

	return Check(CheckValue);
}

bool FBinaryAttributeCondition::CheckCondition(const UAbilitySystemComponent* ASC, const FOnAttributeChangeData& AttributeChangeData) const
{
	if(AttributeChangeData.Attribute != Attribute or !IsValid(ASC))
	{
		return false;
	}

	float CheckValue = AttributeChangeData.NewValue;
	if(bPercent)
	{
		if(!BackAttribute.IsValid() || !ASC->HasAttributeSetForAttribute(BackAttribute))
		{
			return false;
		}
		
		float BackAttributeValue = ASC->GetNumericAttribute(BackAttribute);
		CheckValue = UKismetMathLibrary::SafeDivide(CheckValue, BackAttributeValue);
	}
	
	return Check(CheckValue);
}

bool FBinaryAttributeCondition::Check(const float CheckValue) const
{
	switch(Condition)
	{
	case EBinaryAttributeConditionType::Equal:
		{
			if(CheckValue == Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::Less:
		{
			if(CheckValue < Value) return true;
		}
	case EBinaryAttributeConditionType::LessOrEqual:
		{
			if(CheckValue <= Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::Greater:
		{
			if(CheckValue > Value) return true;
			break;
		}
	case EBinaryAttributeConditionType::GreaterOrEqual:
		{
			if(CheckValue >= Value) return true;
		}
	}

	return false;
}
