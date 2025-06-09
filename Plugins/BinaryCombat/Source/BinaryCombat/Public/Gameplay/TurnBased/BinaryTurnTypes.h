#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "BinaryTurnTypes.generated.h"

class UBinaryPawnTurnComponent;

namespace BinaryCombatTags
{
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_StartTurn);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_EndTurn);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_PlayerActionStart);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_PlayerActionReceive);
}

UENUM(BlueprintType)
enum class EBinaryTurnActionType: uint8
{
	Invalid,
	Default,
};

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

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBinaryPawnTurnComponent> PawnTurnComponent;

	EBinaryTurnActionType ActionType = EBinaryTurnActionType::Invalid;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnCommonMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FBinaryTurnAction TurnActionData;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnPlayerAction
{
	GENERATED_BODY()
	
};










