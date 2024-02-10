
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

struct FMyGameplayTags
{
public:
	static const FMyGameplayTags Get() { return GameplayTags; }

	static void InitilazingNativeTags();

	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_LightAttack;

protected:

	void AddAllTags(UGameplayTagsManager& Manager);	//Registers all of the tags with the GameplayTags Manager

	void AddTag(FGameplayTag& OutTag,const ANSICHAR* TagName,const ANSICHAR* TagComment);

private:
	static FMyGameplayTags GameplayTags;

	
};

