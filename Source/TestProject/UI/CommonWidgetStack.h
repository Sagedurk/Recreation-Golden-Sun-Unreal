// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonWidgetStack.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UCommonWidgetStack : public UCommonActivatableWidgetStack
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	int GetIndex(UCommonActivatableWidget* Widget);

	UFUNCTION(BlueprintCallable)
	int GetAmountOfWidgets();

	UFUNCTION(BlueprintCallable)
	int GetNumOfWidgetsStackedInFrontOf(UCommonActivatableWidget* Widget);
};
