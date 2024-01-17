// Fill out your copyright notice in the Description page of Project Settings.


#include "AdeptClassSeries.h"

#include "AdeptClass.h"


// Sets default values
AAdeptClassSeries::AAdeptClassSeries()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdeptClassSeries::BeginPlay()
{
	Super::BeginPlay();


	DatabaseMap = ConvertDatabaseToMap(Classes);
}

void AAdeptClassSeries::GetGameInstanceReferences()
{
	Super::GetGameInstanceReferences();
}

bool AAdeptClassSeries::MeetsSeriesRequirement(AAdept* Adept)
{
	for (FSeriesAvailability Availability : Requirements)
	{
		if(Adept->BaseElement != Availability.AdeptElement)
			continue;

		for (EElementalType Element : Availability.MajorDjinnElements)
		{
			if(Adept->GetDjinnAmount(Element) <= 0)
				return false;
		}

		return true;
	}


	return false;
}

bool AAdeptClassSeries::MeetsDjinnRequirement(AAdept* Adept, FClassAvailability ClassAvailability)
{
	for (FClassDjinnRequirement DjinnRequirement : ClassAvailability.DjinnRequirement)
	{
		if(Adept->GetDjinnAmount(DjinnRequirement.DjinnElement, EDjinniState::Standby) < DjinnRequirement.DjinnAmount)
			return false;
	}

	return true;
}

void AAdeptClassSeries::PopulateClassPsynergies(AAdeptClass* AdeptClass)
{
	if(AdeptClass == nullptr)
		return;
	
	for (FPsynergyAvailability Psynergy : Psynergies)
	{
		int RequiredSeriesTier = Psynergy.ClassRequirement.GetDefaultObject()->ClassTier;

		if(AdeptClass->ClassTier >= RequiredSeriesTier)
			AdeptClass->Psynergies.Add(Psynergy);
	}
}


AAdeptClass* AAdeptClassSeries::GetSeriesClass(AAdept* Adept)
{
	const FString* ClassName = nullptr;

	for (TSubclassOf<AAdeptClass> AdeptClass  : Classes)
	{
		for (FClassAvailability ClassAvailability : AdeptClass.GetDefaultObject()->ClassAvailability)
		{
			if(Adept->BaseElement != ClassAvailability.AdeptElement)
				continue;
			
			if(MeetsDjinnRequirement(Adept, ClassAvailability))
			{
				ClassName = DatabaseMap.FindKey(AdeptClass);
				break;
			}
		}
	}
	
	if(ClassName == nullptr)
		return nullptr;
	
	AAdeptClass* AdeptClass = GetDatabaseItem(*ClassName, &SpawnedClasses, &DatabaseMap);

	if(AdeptClass != nullptr && AdeptClass->Psynergies.IsEmpty())
		PopulateClassPsynergies(AdeptClass);
	
	return AdeptClass;
}

// Called every frame
void AAdeptClassSeries::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

