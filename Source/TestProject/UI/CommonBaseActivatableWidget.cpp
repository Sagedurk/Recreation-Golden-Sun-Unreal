// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonBaseActivatableWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"

void UCommonBaseActivatableWidget::TryShiftInParent(int NewIndex)
{
	if(!HasParent())
		return;
	
	ShiftInParent(NewIndex);
}

void UCommonBaseActivatableWidget::TryMoveToFront()
{
	if(!HasParent())
		return;

	ShiftInParent(Parent->GetChildrenCount() - 1);
}

void UCommonBaseActivatableWidget::TryMoveToBack()
{
	if(!HasParent())
		return;

	ShiftInParent(0);
}

void UCommonBaseActivatableWidget::ShiftInParent(int ZOrder)
{
	if(UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		PanelSlot->SetZOrder(ZOrder);
		Parent->InvalidateLayoutAndVolatility();
	}
}

bool UCommonBaseActivatableWidget::HasParent()
{
	Parent = GetParent();
	
	if(Parent == nullptr)
		return false;

	return true;
}
