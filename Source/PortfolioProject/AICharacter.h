// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();
	
	UBehaviorTree* GetBehaviorTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI",meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};

