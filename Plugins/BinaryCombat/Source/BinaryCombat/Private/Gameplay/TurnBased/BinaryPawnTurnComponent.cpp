// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Ability/AttributeSet/BinaryAttributeSet_Combat.h"

void UBinaryPawnTurnComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	check(OwningAbilitySystemComponent);
}

float UBinaryPawnTurnComponent::GetTurnSpeed() const
{
	return OwningAbilitySystemComponent->GetNumericAttribute(UBinaryAttributeSet_Combat::GetSpeedAttribute());
}
