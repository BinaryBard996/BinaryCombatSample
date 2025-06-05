#pragma once

#include "CoreMinimal.h"
#include "BinaryTurnTypes.generated.h"

class UBinaryPawnTurnComponent;

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> TurnPawn;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBinaryPawnTurnComponent> PawnTurnComponent;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> TurnPawn;
};










