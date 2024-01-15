// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonBaseActivatableWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UCommonBaseActivatableWidget : public UCommonActivatableWidget
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
	bool HasParent();
};
