#include "Gameplay/TurnBased/BinaryTurnTypes.h"

namespace BinaryCombatTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_StartTurn, "Message.Turn.StartTurn", "回合消息-回合开始")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_EndTurn, "Message.Turn.StartTurn", "回合消息-回合结束")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_PlayerActionStart, "Message.Turn.PlayerActionStart", "回合消息-玩家行动开始")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Turn_PlayerActionReceive, "Message.Turn.PlayerActionReceive", "回合消息-收到玩家行动回调")
}
