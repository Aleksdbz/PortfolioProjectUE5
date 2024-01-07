// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "AICharacter.generated.h"


class ASword;

UCLASS()
class PORTFOLIOPROJECT_API AAICharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();
	
	UBehaviorTree* GetBehaviorTree();
	UPROPERTY(EditAnywhere)
	ASword* Sword;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASword> SwordClass;


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

	UAnimMontage* GetMontage() const;

	int MeleeAttack_Implementation() override;
	
private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetUpStimulusSource();
	//virtual float PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Ai", meta =(AllowPrivateAccess = "true"))
	UAnimMontage* Montage;
};

