// Fill out your copyright notice in the Description page of Project Settings.


#include "Teams/BinaryTeamAgentInterface.h"

#include "BinaryCombatLog.h"

UBinaryTeamAgentInterface::UBinaryTeamAgentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IBinaryTeamAgentInterface::ConditionalBroadcastTeamChanged(TScriptInterface<IBinaryTeamAgentInterface> This,
	FGenericTeamId OldTeamID, FGenericTeamId NewTeamID)
{
	if(OldTeamID != NewTeamID)
	{
		const int32 OldTeamIndex = GenericTeamIdToInteger(OldTeamID);
		const int32 NewTeamIndex = GenericTeamIdToInteger(NewTeamID);
		UObject* ThisObj = This.GetObject();

		UE_LOG(LogBinary, Verbose, TEXT("[%s] %s assigned team %d"), *GetClientServerContextString(ThisObj), *GetPathNameSafe(ThisObj), NewTeamIndex);

		This.GetInterface()->GetTeamChangedDelegateChecked().Broadcast(ThisObj, OldTeamIndex, NewTeamIndex);
	}
}
