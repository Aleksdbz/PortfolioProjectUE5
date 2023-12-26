// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_AIController.h"
#include "AICharacter.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& ObjectInitializer)
{
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
