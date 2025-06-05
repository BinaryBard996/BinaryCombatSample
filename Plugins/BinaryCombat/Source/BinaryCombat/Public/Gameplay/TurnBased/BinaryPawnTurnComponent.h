// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/PawnComponent.h"
#include "BinaryPawnTurnComponent.generated.h"


UCLASS(ClassGroup=(BinaryTurn), meta=(BlueprintSpawnableComponent))
class BINARYCOMBAT_API UBinaryPawnTurnComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Component interface
	virtual void BeginPlay() override;
	// ~Component interface
	
	float GetTurnSpeed() const;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwningAbilitySystemComponent;
	
};
