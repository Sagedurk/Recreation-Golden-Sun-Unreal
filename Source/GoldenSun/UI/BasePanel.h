// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "BasePanel.generated.h"

/**
 * 
 */
UENUM()
enum class EPanelType : int8
{
	Horizontal = 0		UMETA(DisplayName = "Horizontal"),
	Vertical = 1		UMETA(DisplayName = "Vertical"),
	Canvas = 2			UMETA(DisplayName = "Canvas"),
};
UCLASS()
class GOLDENSUN_API UBasePanel : public UCanvasPanel
{
	GENERATED_BODY()

	

public:

	UPROPERTY(EditInstanceOnly)
	EPanelType PanelType;
	
	UFUNCTION(BlueprintCallable)
	void CalculateSize();
	void CalculateCanvas();

	void CalculateHorizontalSize();
	void CalculateVerticalSize();
	void SetSize(FVector2D NewSize);

	UCanvasPanelSlot* GetChildSlot(UWidget* Child);
	void SetAnchor(UCanvasPanelSlot* CanvasSlot, FVector2D Maximum, FVector2D Minimum);
	void SetAnchor(UCanvasPanelSlot* CanvasSlot, FVector2D AnchorVector);
};
