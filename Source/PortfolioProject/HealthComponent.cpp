
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth =  100;

	
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    
	AActor* MyOwner = GetOwner(); //get owner of actor
	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::HandleTakeDamage);
		
	}
	Health = MaxHealth;
	
}

void UHealthComponent::HandleTakeDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f) return;;
	Health = FMath::Clamp(Health - Damage, 0.0f,MaxHealth);
	OnHealthChanged.Broadcast(this,Health,Damage,DamageType,InstigatedBy,DamageCauser);

		
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

