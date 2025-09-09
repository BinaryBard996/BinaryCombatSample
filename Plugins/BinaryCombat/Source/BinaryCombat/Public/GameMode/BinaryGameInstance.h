// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BinaryGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BINARYCOMBAT_API UBinaryGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
};
