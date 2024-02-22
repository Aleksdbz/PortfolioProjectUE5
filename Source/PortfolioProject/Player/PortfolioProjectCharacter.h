// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Logging/LogMacros.h"
#include "UE5Coro.h"
#include "PortfolioProjectCharacter.generated.h"

struct FOnAttributeChangeData;
struct FGameplayAttribute;
class UInputConfig;
struct FGameplayTag;
class UMyEnhancedInputComponent;
class ASword;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABow;

class AArrow;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APortfolioProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BlockAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LightAttack;



public:
	APortfolioProjectCharacter();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= InputAnimation, meta =(AllowPrivateAccess = "true"))
	bool IsSlashing;
	
	UPROPERTY(EditAnywhere)
	ASword* Sword;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASword> SwordClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	UPROPERTY()
	class UMyAttributeSet* AttributesSet;
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category ="Abilities")
	TArray<TSubclassOf< class UMyGameplayAbility>> GameplayAbility;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) //Default Attributes for Player 
	TSubclassOf<class UGameplayEffect> DefaultGameplayEffect;
	
	//void InitializeAttributes();

	virtual void GrandAbilities();

	void MappingContext();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& InputActionValue);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& InputActionValue);
	void StartBlock(const FInputActionValue& InputActionValue);		
	void StopBlock(const FInputActionValue& InputActionValue);
	void StartLightAttack(const FInputActionValue& InputActionValue);

	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
private:
	void EquipSword();
	UE5Coro::TCoroutine<> StartAttack(UAnimMontage* Montage);
	int ComboCount ;
	bool isAttacking;

	UAnimInstance* GetAnimInstance() const;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputConfig* InputConfig;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "PlayerCombatAnimation", meta =(AllowPrivateAccess = "true"))
	UAnimMontage* SwordAttack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "PlayerCombatAnimation", meta =(AllowPrivateAccess = "true"))
	UAnimMontage* SwordAttack2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "PlayerCombatAnimation", meta =(AllowPrivateAccess = "true"))
    UAnimMontage* SwordAttack3;

	
	
};



