// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	UPanelWidget* Parent;

	
	
	UFUNCTION(BlueprintCallable)
	void TryShiftInParent(int NewIndex);

	UFUNCTION(BlueprintCallable)
	void TryMoveToFront();

	UFUNCTION(BlueprintCallable)
	void TryMoveToBack();


private:

	void ShiftInParent(int ZOrder);
	void SetParent(UWidget* Target, UPanelWidget* NewParent);
	bool HasParent();
	
};
