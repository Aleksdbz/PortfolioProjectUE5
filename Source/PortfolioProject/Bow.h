// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bow.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API ABow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABow();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* Root;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
