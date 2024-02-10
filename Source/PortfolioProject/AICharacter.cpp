// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Sword.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetUpStimulusSource();
	

}


void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
		Sword = GetWorld()->SpawnActor<ASword>(SwordClass);
		Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_lSocket"));
		Sword->SetOwner(this);
	
	
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


