#include "BTService_IsTargetInRange.h"
#include "AICharacter.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UBTService_IsTargetInRange::UBTService_IsTargetInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Melee Range");
}

void UBTService_IsTargetInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	// GET NPC AND CONTROLLER
	auto const* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	auto const* const npc = Cast<AAICharacter>(cont->GetPawn());
	//GET PLAYER CHAR
	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),
		npc->GetDistanceTo(player) <= MeleeRange);
	
}


	

