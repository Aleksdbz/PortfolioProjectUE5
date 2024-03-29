// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UCapsuleComponent* CapsuleColider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
