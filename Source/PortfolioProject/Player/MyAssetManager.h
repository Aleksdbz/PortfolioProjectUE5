// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"


UCLASS()
class PORTFOLIOPROJECT_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UMyAssetManager();

	//Return the AssetManager singleton object
	static UMyAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;




	
};
