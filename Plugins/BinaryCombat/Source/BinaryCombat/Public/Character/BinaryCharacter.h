// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularCharacter.h"
#include "GameFramework/Character.h"
#include "Teams/BinaryTeamAgentInterface.h"
#include "BinaryCharacter.generated.h"

class UBinaryAbilitySystemComponent;

UCLASS()
class BINARYCOMBAT_API ABinaryCharacter: public AModularCharacter, public IBinaryTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABinaryCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// ~Actor interface

	// IBinaryTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnBinaryTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override;
	// ~IBinaryTeamAgentInterface

protected:
	UPROPERTY(Replicated)
	FGenericTeamId MyTeamId;

	UPROPERTY()
	FOnBinaryTeamIndexChangedDelegate OnTeamChangedDelegate;
};
