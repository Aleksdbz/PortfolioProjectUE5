// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PortfolioProject/AI/AICharacter.h"
#include "PortfolioProject/AI/CombatInterface.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 Super::ExecuteTask(OwnerComp, NodeMemory);

	//if we are out of range do not attack the player
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if(OutOfRange)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	//we are in range so we get ai cont, and NPC
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const  npc = Cast<AAICharacter>(cont->GetPawn());

	//IF THE NPC supports combat interface castr and call Melee attack function
	if(auto* const iCombat = Cast<ICombatInterface>(npc))
	{
		if(MontageHasFinished(npc))
		{
			//must check to see if montage has finished so we dont try and play it again
			iCombat->Execute_MeleeAttack(npc);
		}
	}
	//finish the task
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::MontageHasFinished(AAICharacter* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
