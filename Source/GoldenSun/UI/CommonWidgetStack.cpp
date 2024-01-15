// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonWidgetStack.h"

int UCommonWidgetStack::GetIndex(UCommonActivatableWidget* Widget)
{
	int Index = -1;
	
	TArray<UCommonActivatableWidget*> Widgets = GetWidgetList();

	if(!Widgets.Contains(Widget))
		return Index;

	for (size_t i = 0; i < Widgets.Num(); i++)
	{
		if(Widgets[i] == Widget)
		{
			Index = i;
			break;
		}
	}

	return Index;
}

int UCommonWidgetStack::GetAmountOfWidgets()
{
	return GetNumWidgets();
}

int UCommonWidgetStack::GetNumOfWidgetsStackedInFrontOf(UCommonActivatableWidget* Widget)
{
	int WidgetIndex = GetIndex(Widget);
	int NumOfWidgets = GetAmountOfWidgets();

	if(WidgetIndex == -1 || WidgetIndex >= NumOfWidgets)
		return -1;

	return NumOfWidgets - WidgetIndex - 1;
}
