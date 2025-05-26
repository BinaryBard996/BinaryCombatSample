// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ModularPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "GameFramework/Pawn.h"
#include "BinaryCameraPawn.generated.h"

UCLASS()
class BINARYCOMBAT_API ABinaryCameraPawn : public AModularPawn
{
	GENERATED_BODY()

public:
	ABinaryCameraPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Binary|Camera")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Binary|Camera")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Binary|Camera")
	TObjectPtr<UGameplayCameraComponent> GameplayCameraComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Camera Settings")
	TObjectPtr<UCameraAsset> DefaultCameraAsset;
	
};
