// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "AICharacter.generated.h"


class UAIUILogic;
struct FGameplayAttribute;
class ASword;
class UWidgetComponent;
class UMyAttributeSet;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, AINewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, AINewMaxHealth);


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
	
	UPROPERTY()
	UAIUILogic* HealthWidget;

	UPROPERTY()
	TSubclassOf<UAIUILogic> HealthWidgetClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWidgetComponent* AIHealthBar;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category ="AI||Abilities")
	TArray<TSubclassOf< class UMyGameplayAbility>> NPCAbilities;
	
	//void GrantAbilities();
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UAbilitySystemComponent* AIAbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AIAbilitySystemComponent;
	}
	
	UPROPERTY()
	TObjectPtr<UMyAttributeSet> AIAttribute;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature AIHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeSignature AIMaxHealthChange;

	void OnAIMaxHealthChange(const FOnAttributeChangeData& Data) const;
	void OnAIHealthChange(const FOnAttributeChangeData& Data) const;

	void GrantAbilities();

protected:
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

	UFUNCTION()
	float GetAiMaxHp()const;

	
	


	
};

