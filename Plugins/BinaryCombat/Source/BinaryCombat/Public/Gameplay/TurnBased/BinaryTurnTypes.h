#pragma once
#include "BinaryTurnTypes.generated.h"

USTRUCT(BlueprintType)
BINARYCOMBAT_API struct FBinaryTurnItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> TurnActor;

};










