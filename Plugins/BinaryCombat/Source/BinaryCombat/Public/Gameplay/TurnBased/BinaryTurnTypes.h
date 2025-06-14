#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "StructUtils/InstancedStruct.h"
#include "BinaryTurnTypes.generated.h"

class UBinaryPawnTurnComponent;

namespace BinaryCombatTags
{
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_StartTurn);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_EndTurn);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_PlayerMakeDecisionStart);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Turn_PlayerMakeDecisionEnd);

	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Turn_Action);
	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Turn_Action_Move);
}

UENUM(BlueprintType)
enum class EBinaryTurnActionType: uint8
{
	Invalid,
	Default,
};

UENUM(BlueprintType)
enum class EBinaryTurnPawnActionType: uint8
{
	Invalid,
	Move
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
struct BINARYCOMBAT_API FBinaryTurn
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> TurnPawn;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBinaryPawnTurnComponent> PawnTurnComponent;

	EBinaryTurnActionType ActionType = EBinaryTurnActionType::Invalid;

	bool IsValidTurn() const;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnCommonMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FBinaryTurn TurnActionData;
};

USTRUCT()
struct BINARYCOMBAT_API FBinaryTurnActionData
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnActionData_Move
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ActionData")
	FVector TargetLocation;
};

USTRUCT(BlueprintType)
struct BINARYCOMBAT_API FBinaryTurnAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APawn> TurnPawn; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(GameplayTagFilter="Turn.Action"))
	FGameplayTag ActionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(BaseStruct="/Script/BinaryCombat.FBinaryTurnActionData", ExcludeBaseStruct))
	FInstancedStruct ActionInstancedData;

	void Reset();
	bool IsValidTurnAction() const;
};










