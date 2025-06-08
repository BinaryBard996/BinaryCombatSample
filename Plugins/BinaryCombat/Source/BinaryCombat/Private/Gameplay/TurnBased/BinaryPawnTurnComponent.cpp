// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TurnBased/BinaryPawnTurnComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BinaryCombatTags.h"
#include "Ability/AttributeSet/BinaryAttributeSet_Combat.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Gameplay/TurnBased/BinaryTurnTypes.h"
#include "Kismet/GameplayStatics.h"

void UBinaryPawnTurnComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	check(OwningAbilitySystemComponent);

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	StartTurnListenerHandle = GameplayMessageSubsystem.RegisterListenerToActor(GetOwner(), BinaryCombatTags::Message_Turn_StartTurn, this, &ThisClass::OnStartTurn);
	EndTurnListenerHandle = GameplayMessageSubsystem.RegisterListenerToActor(GetOwner(), BinaryCombatTags::Message_Turn_StartTurn, this, &ThisClass::OnEndTurn);
}

void UBinaryPawnTurnComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(this);
	GameplayMessageSubsystem.UnregisterListener(StartTurnListenerHandle);
	GameplayMessageSubsystem.UnregisterListener(EndTurnListenerHandle);
}

void UBinaryPawnTurnComponent::OnStartTurn(FGameplayTag MessageTag, const FBinaryTurnCommonMessage& MessageData)
{
	// Tick Turn
	UAbilitySystemBlueprintLibrary::TickTurn(OwningAbilitySystemComponent, 1);
}

void UBinaryPawnTurnComponent::OnEndTurn(FGameplayTag MessageTag, const FBinaryTurnCommonMessage& MessageData)
{
	
}

float UBinaryPawnTurnComponent::GetTurnSpeed() const
{
	return OwningAbilitySystemComponent->GetNumericAttribute(UBinaryAttributeSet_Combat::GetSpeedAttribute());
}
