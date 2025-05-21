// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BinaryCharacter.h"
#include "BinaryCharacterWithAbilities.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API ABinaryCharacterWithAbilities : public ABinaryCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABinaryCharacterWithAbilities(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// IAbilitySystemInterface
	UFUNCTION(BlueprintCallable, Category="Binary|Character")
	UBinaryAbilitySystemComponent* GetBinaryAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~IAbilitySystemInterface

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Binary|Character")
	TObjectPtr<UBinaryAbilitySystemComponent> AbilitySystemComponent;
	
};
