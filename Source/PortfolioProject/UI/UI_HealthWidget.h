
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_HealthWidget.generated.h"

class UMyAttributeSet;
class UProgressBar;

UCLASS()
class PORTFOLIOPROJECT_API UUI_HealthWidget : public UUserWidget
{ 
	GENERATED_BODY()

public:

	

	UPROPERTY(BlueprintReadWrite, Category="Custom UI", meta=(BindWidget))
	class UCanvasPanel* CanvasWidget;
	
	UPROPERTY(BlueprintReadWrite, Category="Custom UI", meta=(BindWidget))
	class UProgressBar* ProgressBarWidget;
	
	UPROPERTY(BlueprintReadWrite, Category="Custom UI", meta=(BindWidget))
	class UTextBlock* HealthTextWidget;

	
	
	void SetCurrentHealth_Implementation(float UIHealth);
};
 