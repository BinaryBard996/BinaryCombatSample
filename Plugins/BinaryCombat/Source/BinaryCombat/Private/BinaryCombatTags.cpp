#include "BinaryCombatTags.h"

namespace BinaryCombatTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Attribute_DamageRate, "Ability.Attribute.DamageRate", "技能属性-技能伤害系数")

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if(!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for(const FGameplayTag& TestTag: AllTags)
			{
				if(TestTag.ToString().Contains(TagString))
				{
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}
