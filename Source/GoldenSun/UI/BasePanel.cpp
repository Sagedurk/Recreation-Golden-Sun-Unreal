// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePanel.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"

void UBasePanel::CalculateSize()
{
	switch (PanelType)
	{
		case EPanelType::Horizontal:
			CalculateHorizontalSize();
			break;
		case EPanelType::Vertical:
			CalculateVerticalSize();
			break;
		case EPanelType::Canvas:
			CalculateCanvas();
			break;
		
	}
	
}

void UBasePanel::CalculateCanvas()
{
	if(USizeBox* SizeBox = Cast<USizeBox>(GetParent()))
	{
		SizeBox->ClearWidthOverride();
		SizeBox->ClearHeightOverride();
	}
}



void UBasePanel::CalculateHorizontalSize()
{
	TArray<UWidget*> Children = GetAllChildren();
	FVector2D TotalSize = FVector2D::Zero(); 
	
	for (size_t i = 0; i < Children.Num(); i++)
	{
		UWidget* Child = Children[i];
		
		if(Child->GetVisibility() == ESlateVisibility::Collapsed)
			continue;
		
		UCanvasPanelSlot* CanvasSlot = GetChildSlot(Child);

		SetAnchor(CanvasSlot, FVector2D(0, 0));
		CanvasSlot->SetPosition(FVector2D(TotalSize.X, 0));

		FVector2D ChildSize = CanvasSlot->GetSize();
	
		TotalSize.X += ChildSize.X;

		if(ChildSize.Y > TotalSize.Y)
			TotalSize.Y = ChildSize.Y;
	}

	SetSize(TotalSize);
}
void UBasePanel::CalculateVerticalSize()
{
	TArray<UWidget*> Children = GetAllChildren();
	FVector2D TotalSize = FVector2D::Zero(); 
	
	for (size_t i = 0; i < Children.Num(); i++)
	{
		UWidget* Child = Children[i];
		
		if(Child->GetVisibility() == ESlateVisibility::Collapsed)
			continue;
		
		UCanvasPanelSlot* CanvasSlot = GetChildSlot(Child);

		SetAnchor(CanvasSlot, FVector2D(0, 0));
		CanvasSlot->SetPosition(FVector2D(0, TotalSize.Y));

		FVector2D ChildSize = CanvasSlot->GetSize();
	
		TotalSize.Y += ChildSize.Y;

		if(ChildSize.X > TotalSize.X)
			TotalSize.X = ChildSize.X;
	}

	SetSize(TotalSize);
}

void UBasePanel::SetSize(FVector2D NewSize)
{
	if(USizeBox* SizeBox = Cast<USizeBox>(GetParent()))
	{
		SizeBox->SetWidthOverride(NewSize.X);
		SizeBox->SetHeightOverride(NewSize.Y);
	}
}



UCanvasPanelSlot* UBasePanel::GetChildSlot(UWidget* Child)
{
	if(UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Child->Slot))
	{
		return CanvasSlot;
	}

	return nullptr;
}

void UBasePanel::SetAnchor(UCanvasPanelSlot* CanvasSlot, FVector2D Maximum, FVector2D Minimum)
{
	FAnchors Anchor;
	Anchor.Maximum = Maximum;
	Anchor.Minimum = Minimum;
		
	CanvasSlot->SetAnchors(Anchor);
	CanvasSlot->SetAlignment(Minimum);
}

void UBasePanel::SetAnchor(UCanvasPanelSlot* CanvasSlot, FVector2D AnchorVector)
{
	SetAnchor(CanvasSlot, AnchorVector, AnchorVector);
}