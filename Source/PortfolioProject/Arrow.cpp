
#include "Arrow.h"

#include "PortfolioProjectCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	CapsuleColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colider"));
	SetRootComponent(StaticMesh);
	CapsuleColider->SetupAttachment(StaticMesh);
	ProjectileMovement->InitialSpeed = 1400.0f;
	ProjectileMovement->MaxSpeed = 1600.0f;




}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


