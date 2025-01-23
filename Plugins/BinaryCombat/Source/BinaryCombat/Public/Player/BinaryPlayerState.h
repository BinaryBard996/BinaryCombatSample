// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BinaryPlayerState.generated.h"

class UBinaryAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API ABinaryPlayerState
	: public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABinaryPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get())
	
	// IAbilitySystemInterface
	UFUNCTION(BlueprintCallable)
	UBinaryAbilitySystemComponent* GetBinaryAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~IAbilitySystemInterface

private:
	UPROPERTY(VisibleAnywhere, Category="Binary|PlayerState")
	TObjectPtr<UBinaryAbilitySystemComponent> AbilitySystemComponent;
};
