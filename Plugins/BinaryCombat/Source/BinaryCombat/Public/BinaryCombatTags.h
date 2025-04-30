#pragma once

#include "NativeGameplayTags.h"

namespace BinaryCombatTags
{
	BINARYCOMBAT_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	BINARYCOMBAT_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attribute_DamageRate);
}
