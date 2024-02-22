// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "AICharacter.generated.h"


class UWidgetComponent;
class UMyAttributeSet;
class ASword;

UCLASS()
class PORTFOLIOPROJECT_API AAICharacter : public ACharacter, public ICombatInterface, public IAbilitySystemInterface
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

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UAbilitySystemComponent* AIAbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AIAbilitySystemComponent;
	}

	UPROPERTY()
	TObjectPtr<UMyAttributeSet> AIAttribute;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>  AIHealthBar;


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

	virtual int MeleeAttack_Implementation() override;
	
private:
	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetUpStimulusSource();
	//virtual float PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Ai", meta =(AllowPrivateAccess = "true"))
	UAnimMontage* Montage;
};

