

#include "AICharacter.h"
#include "AbilitySystemComponent.h"
#include "NPC_AIController.h"
#include "Components/WidgetComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "PortfolioProject/Items/Sword.h"
#include "PortfolioProject/Player/MyAttributeSet.h"
#include "PortfolioProject/Player/MyGameplayAbility.h"
#include "PortfolioProject/UI/AIUILogic.h"

// Sets default values
AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SetUpStimulusSource();

	AIHealthBar = CreateDefaultSubobject<UWidgetComponent>("AIHealthBar");
	AIHealthBar->SetupAttachment(GetRootComponent());

	AIAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AIAbilitySystemComp");
	AIAttribute = CreateDefaultSubobject<UMyAttributeSet>("AIAttributes");

}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
		Sword = GetWorld()->SpawnActor<ASword>(SwordClass);
		Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_lSocket"));
		Sword->SetOwner(this);
	AIAttribute->SetMaxHealth(2000);
	AIAttribute->SetHealth(2000);
	
	AIHealthChange.Broadcast(AIAttribute->GetHealth());
	AIMaxHealthChange.Broadcast(AIAttribute->GetMaxHealth());
	
	auto const AiHealth = AIAttribute->GetHealthAttribute();
	auto const GetAIMaxHp  = AIAttribute->GetMaxHealthAttribute();
	

	AIAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AiHealth).AddUObject(this,&AAICharacter::OnAIHealthChange);
	AIAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAIMaxHp).AddUObject(this,&AAICharacter::OnAIMaxHealthChange);

	AIAbilitySystemComponent->InitAbilityActorInfo(this,this);
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::SetUpStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if(StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

float AAICharacter::GetAiMaxHp() const
{
	return AIAttribute->GetMaxHealth();
}


void AAICharacter::GrantAbilities()
{
	for(TSubclassOf<UGameplayAbility> AIAbilities : NPCAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AIAbilities, 1);
			
			AIAbilitySystemComponent->GiveAbility(AbilitySpec);
		
	}
	

}

void AAICharacter::OnAIMaxHealthChange(const FOnAttributeChangeData& Data) const
{
	
	AIMaxHealthChange.Broadcast(Data.NewValue);

}

void AAICharacter::OnAIHealthChange(const FOnAttributeChangeData& Data) const
{
	AIHealthChange.Broadcast(Data.NewValue);
	
}

UBehaviorTree* AAICharacter::GetBehaviorTree()
{
	return Tree;
}
UAnimMontage* AAICharacter::GetMontage() const
{
	return Montage;
}

int AAICharacter::MeleeAttack_Implementation()
{
	if(Montage)
	{
		PlayAnimMontage(Montage);
	}
	return 0;
}


