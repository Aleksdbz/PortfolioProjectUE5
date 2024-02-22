
#include "Sword.h"
#include "Components/BoxComponent.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);
	
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Colider"));
	BoxCollider->SetupAttachment(GetRootComponent());
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Bot Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnBoxHit);
	
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASword::OnBoxHit(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FVector Start = BoxTraceStart->GetComponentLocation();
	FVector End = BoxTraceEnd->GetComponentLocation();
	TArray<AActor*> ActorIgnore;
	ActorIgnore.Add(this);
	const FVector Size (5.0f,5.0f,5.0f);
	FHitResult HitRes;
	
	UKismetSystemLibrary::BoxTraceSingle(this,
		Start,
		End,
		Size,
		BoxTraceStart->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorIgnore,
		EDrawDebugTrace::ForDuration,
		HitRes,
		true);

	if(HitRes.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitRes.GetActor()->GetName()); 

	}



	
}
		



