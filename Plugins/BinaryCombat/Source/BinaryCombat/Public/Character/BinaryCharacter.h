// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BinaryCharacter.generated.h"

class UBinaryAbilitySystemComponent;

UCLASS()
class BINARYCOMBAT_API ABinaryCharacter
	: public ACharacter
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABinaryCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ~Actor interface

	// IAbilitySystemInterface
	UFUNCTION(BlueprintCallable, Category="Binary|Character")
	UBinaryAbilitySystemComponent* GetBinaryAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~IAbilitySystemInterface

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Binary|Character")
	TObjectPtr<UBinaryAbilitySystemComponent> AbilitySystemComponent;

};
