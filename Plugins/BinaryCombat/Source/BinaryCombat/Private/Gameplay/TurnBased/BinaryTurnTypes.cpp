#include "Gameplay/TurnBased/BinaryTurnTypes.h"
#include "GameFramework/Pawn.h"

namespace BinaryCombatTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_StartTurn, "Message.Turn.StartTurn", "回合消息-回合开始")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_EndTurn, "Message.Turn.StartTurn", "回合消息-回合结束")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_PlayerMakeDecisionStart, "Message.Turn.PlayerMakeDecisionStart", "回合消息-玩家开始做决策")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_PlayerMakeDecisionEnd, "Message.Turn.PlayerMakeDecisionEnd", "回合消息-玩家结束做决策")
}

void FBinaryTurnAction::Reset()
{
	ActionType = EBinaryTurnPawnActionType::Invalid;
	TurnPawn = nullptr;
	ActionInstancedData.Reset();
}

bool FBinaryTurnAction::IsValidTurnAction() const
{
	return ActionType != EBinaryTurnPawnActionType::Invalid && IsValid(TurnPawn);
}