// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"

void UBaseWidget::TryShiftInParent(int NewIndex)
{
	if(!HasParent())
		return;
	
	ShiftInParent(NewIndex);
}

void UBaseWidget::TryMoveToFront()
{
	if(!HasParent())
		return;

	ShiftInParent(Parent->GetChildrenCount() - 1);
}

void UBaseWidget::TryMoveToBack()
{
	if(!HasParent())
		return;

	ShiftInParent(0);
}

void UBaseWidget::ShiftInParent(int ZOrder)
{
	if(UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot))
	 {
	 	PanelSlot->SetZOrder(ZOrder);
		Parent->InvalidateLayoutAndVolatility();
		
	 }
}

void UBaseWidget::SetParent(UWidget* Target, UPanelWidget* NewParent)
{	
	Target->RemoveFromParent();

	NewParent->AddChild(Target);
}



bool UBaseWidget::HasParent()
{
	Parent = GetParent();
	
	if(Parent == nullptr)
		return false;

	return true;
}
