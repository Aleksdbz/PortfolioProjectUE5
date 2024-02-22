
#include "ProjectPlayerState.h"
#include "Player/MyAttributeSet.h"

AProjectPlayerState::AProjectPlayerState()
{
	
	Attribute = CreateDefaultSubobject<UMyAttributeSet>("CharAtt");
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySysComp");
}

void AProjectPlayerState::OnHealthChange(const FOnAttributeChangeData& Data) const
{
	HealthChange.Broadcast(Data.NewValue);

}

void AProjectPlayerState::OnMaxHealthChange(const FOnAttributeChangeData& Data) const
{
	MaxHealthChange.Broadcast(Data.NewValue);
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed: %f"), Data.OldValue);

}


void AProjectPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	auto const PlayerHealth = Attribute->GetHealthAttribute();
	auto const PlayerMaxHealth = Attribute->GetMaxHealthAttribute();

	
	HealthChange.Broadcast(Attribute->GetHealth());
	MaxHealthChange.Broadcast(Attribute->GetMaxHealth());
	
	
	ASC->GetGameplayAttributeValueChangeDelegate(PlayerHealth).AddUObject(this,&AProjectPlayerState::OnHealthChange);
	ASC->GetGameplayAttributeValueChangeDelegate(PlayerMaxHealth).AddUObject(this,&AProjectPlayerState::OnMaxHealthChange);
	
}


UAbilitySystemComponent* AProjectPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

