// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/PawnComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "BinaryPawnTurnComponent.generated.h"

struct FBinaryTurnCommonMessage;

UCLASS(ClassGroup=(BinaryTurn), meta=(BlueprintSpawnableComponent))
class BINARYCOMBAT_API UBinaryPawnTurnComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Component interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// ~Component interface

	// Turn Flow Functions
	virtual void OnStartTurn(FGameplayTag MessageTag, const FBinaryTurnCommonMessage& MessageData);
	virtual void OnEndTurn(FGameplayTag MessageTag, const FBinaryTurnCommonMessage& MessageData);
	// ~Turn Flow Functions
	
	float GetTurnSpeed() const;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwningAbilitySystemComponent;

	FGameplayMessageListenerHandle StartTurnListenerHandle;
	FGameplayMessageListenerHandle EndTurnListenerHandle;
};
