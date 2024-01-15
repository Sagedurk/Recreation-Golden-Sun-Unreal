// Fill out your copyright notice in the Description page of Project Settings.


#include "AdeptClass.h"

#include "Adept.h"
#include "TestProject/Element.h"

// Sets default values
AAdeptClass::AAdeptClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdeptClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdeptClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FClassAvailability AAdeptClass::TryGetAdeptAvailability(EElementalType AdeptElement)
{
	for (FClassAvailability Availability : ClassAvailability)
	{
		if(Availability.AdeptElement == AdeptElement)
			return Availability;
	}
	return {};
}

TArray<EElementalType> AAdeptClass::GetClassElements(FClassAvailability Availability)
{
	TArray<EElementalType> Elements;
	Elements.Add(Availability.AdeptElement);
	
	for (FClassDjinnRequirement DjinnRequirement : Availability.DjinnRequirement)
	{
		if(!Elements.Contains(DjinnRequirement.DjinnElement))
			Elements.Add(DjinnRequirement.DjinnElement);
	}

	return Elements;
}

float AAdeptClass::GetPercentageMultiplierOfMaximumDjinn(FClassAvailability Availability, AAdept* Adept)
{
	float PercentageMultiplier = 0.0f;
	for (FClassDjinnRequirement DjinnRequirement : Availability.DjinnRequirement)
	{
		if(DjinnRequirement.MaximumDjinnAmount < DjinnRequirement.DjinnAmount)
			return 1.0f;
		
		PercentageMultiplier += static_cast<float>(Adept->GetDjinnAmount(DjinnRequirement.DjinnElement, EDjinniState::Standby)) / static_cast<float> (DjinnRequirement.MaximumDjinnAmount);
	}

	PercentageMultiplier = PercentageMultiplier / Availability.DjinnRequirement.Num();

	PercentageMultiplier = FMath::Clamp(PercentageMultiplier, 0.0f, 1.0f);
	
	return PercentageMultiplier;
}

int32 AAdeptClass::GetDjinnAmount(FClassAvailability Availability)
{
	int32 DjinnAmount = 0;

	for (FClassDjinnRequirement DjinnRequirement : Availability.DjinnRequirement)
	{
		DjinnAmount += DjinnRequirement.DjinnAmount;
	}
	

	return DjinnAmount;
}

int32 AAdeptClass::GetDjinnAmount(FClassAvailability Availability, EElementalType DjinnElement)
{
	int32 DjinnAmount = 0;

	for (FClassDjinnRequirement DjinnRequirement : Availability.DjinnRequirement)
	{
		if(DjinnRequirement.DjinnElement == DjinnElement)
			DjinnAmount += DjinnRequirement.DjinnAmount;
	}
	

	return DjinnAmount;
}

EElementalType AAdeptClass::GetMajorElement(FClassAvailability Availability)
{
	int MajorDjinnAmount = 0;
	EElementalType MajorElement = EElementalType::None;
	
	for (FClassDjinnRequirement DjinnRequirement : Availability.DjinnRequirement)
	{
		if(DjinnRequirement.DjinnAmount > MajorDjinnAmount)
			MajorElement = DjinnRequirement.DjinnElement;
	}

	return MajorElement;
}
