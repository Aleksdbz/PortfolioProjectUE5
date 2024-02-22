

#include "AICharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "PortfolioProject/Items/Sword.h"
#include "PortfolioProject/Player/MyAttributeSet.h"

// Sets default values
AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SetUpStimulusSource();

	AIAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AIAbilitySystemComp");
	AIAttribute = CreateDefaultSubobject<UMyAttributeSet>("AIAttributes");
	AIHealthBar = CreateDefaultSubobject<UWidgetComponent>("AIHealthBar");
	AIHealthBar->SetupAttachment(GetRootComponent());
	

}


void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
		Sword = GetWorld()->SpawnActor<ASword>(SwordClass);
		Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_lSocket"));
		Sword->SetOwner(this);

	AIAttribute->SetHealth(2000);
	AIAttribute->SetMaxHealth(2000);

	
	
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


