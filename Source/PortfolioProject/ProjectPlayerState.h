
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GameplayEffectTypes.h"
#include "ProjectPlayerState.generated.h"

class UAbilitySystemComponent;
class APortfolioProjectCharacter;
struct FOnAttributeChangeData;
class UMyAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);

UCLASS()
class PORTFOLIOPROJECT_API AProjectPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AProjectPlayerState();

	void OnMaxHealthChange(const FOnAttributeChangeData& Data)const;
	void OnHealthChange(const FOnAttributeChangeData& Data)const;

	virtual void BeginPlay() override;
	
    UPROPERTY()
	TObjectPtr<UMyAttributeSet> Attribute;
	
    UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature HealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature MaxHealthChange;
	
	
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	
};

