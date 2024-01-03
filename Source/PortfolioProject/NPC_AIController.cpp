// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_AIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& ObjectInitializer)
{
	SetUpPerceptionSystem();
}

void ANPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(AAICharacter* const AIchar = Cast<AAICharacter>(InPawn))
	{
		if(UBehaviorTree* const Tree = AIchar->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset,b);
			Blackboard = b;
			RunBehaviorTree(Tree);
		}
	}
	
}

void ANPC_AIController::SetUpPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if(SightConfig)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Sight Config found."));

		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Componenet")));
		SightConfig->SightRadius = 500.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,&ANPC_AIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);

		UE_LOG(LogTemp, Warning, TEXT("Perception system set up."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find Sight Config."));
	}
	}

	
	


void ANPC_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{

	if(auto* const ch = Cast<AAICharacter>(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target detected: %s"), *Actor->GetName());

		GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"),Stimulus.WasSuccessfullySensed());
		UE_LOG(LogTemp, Warning, TEXT("CanSeePlayer: %s"), Stimulus.WasSuccessfullySensed() ? TEXT("True") : TEXT("False"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast actor to AAICharacter."));
	}
}
