// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* BoxTraceStart;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* BoxTraceEnd;

	UFUNCTION()
	void OnBoxHit(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
private:


};
