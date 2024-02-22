// Fill out your copyright notice in the Description page of Project Settings.


#include "AsynchTaskOnAttributeChange.h"

#include "AbilitySystemComponent.h"

UAsynchTaskOnAttributeChanged* UAsynchTaskOnAttributeChanged::ListenForAttributeChange
(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UAsynchTaskOnAttributeChanged* WaitForAttributeChangedTask = NewObject<UAsynchTaskOnAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(Attribute).AddUObject(WaitForAttributeChangedTask, &UAsynchTaskOnAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UAsynchTaskOnAttributeChanged * UAsynchTaskOnAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UAsynchTaskOnAttributeChanged* WaitForAttributeChangedTask = NewObject<UAsynchTaskOnAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UAsynchTaskOnAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UAsynchTaskOnAttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAsynchTaskOnAttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}