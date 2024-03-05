// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIUILogic.generated.h"

class UProgressBar;

UCLASS(Blueprintable)
class PORTFOLIOPROJECT_API UAIUILogic : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Custom UI", meta=(BindWidget))
	TObjectPtr<UProgressBar> AIProgressBar;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetCurrentHealth(float UIHealth);
	
};
