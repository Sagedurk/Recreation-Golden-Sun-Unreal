// Fill out your copyright notice in the Description page of Project Settings.


#include "AdeptClassSeriesDatabase.h"

#include "TestProject/Element.h"
#include "TestProject/Combat/AdeptClassSeries.h"

AAdeptClassSeriesDatabase::AAdeptClassSeriesDatabase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAdeptClassSeriesDatabase::BeginPlay()
{
	Super::BeginPlay();

	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetAdeptClassSeriesDatabase(this);
	}

	DatabaseMap = ConvertDatabaseToMap(Database);
}

void AAdeptClassSeriesDatabase::GetGameInstanceReferences()
{
	Super::GetGameInstanceReferences();
}

bool AAdeptClassSeriesDatabase::MeetsDjinnRequirement(AAdept* Adept, FClassAvailability ClassAvailability)
{
	for (FClassDjinnRequirement DjinnRequirement : ClassAvailability.DjinnRequirement)
	{
		if(Adept->GetDjinnAmount(DjinnRequirement.DjinnElement, EDjinniState::Standby) < DjinnRequirement.DjinnAmount)
			return false;
	}

	return true;
}

AAdeptClass* AAdeptClassSeriesDatabase::SortPossibleAdeptClasses(TArray<AAdeptClass*> PossibleClasses, AAdept* Adept)
{
	AAdeptClass* ClassToSet = PossibleClasses[0];

	for (size_t i = 1; i < PossibleClasses.Num(); i++)
	{
		/* ----- Variable Start ----- */
		AAdeptClass* NextClass = PossibleClasses[i];
		
		FClassAvailability NextClassAvailability = NextClass->TryGetAdeptAvailability(Adept->BaseElement);
		FClassAvailability PreviousClassAvailability = ClassToSet->TryGetAdeptAvailability(Adept->BaseElement);

		float NextClassDjinnPercentage = NextClass->GetPercentageMultiplierOfMaximumDjinn(NextClassAvailability, Adept);
		float PreviousClassDjinnPercentage = ClassToSet->GetPercentageMultiplierOfMaximumDjinn(PreviousClassAvailability, Adept);

		TArray<EElementalType> NextClassElements = NextClass->GetClassElements(NextClassAvailability);
		TArray<EElementalType> PreviousClassElements = ClassToSet->GetClassElements(PreviousClassAvailability);
		
		EElementalType NextClassMajorElement = NextClass->GetMajorElement(NextClassAvailability);
		EElementalType PreviousClassMajorElement = ClassToSet->GetMajorElement(PreviousClassAvailability);
		
		EElementalType AdeptUnrelatedElement = FElement::GetUnrelatedElement(Adept->BaseElement);
		EElementalType AdeptOppositeElement = FElement::GetOppositeElement(Adept->BaseElement);
		EElementalType AdeptSymbioticElement = FElement::GetSymbioticElement(Adept->BaseElement);

		/* ----- Variable End ----- */


		
		/* CLASS SERIES TYPE - (Mono-, Dual-, Tri-element) */
		if(NextClassElements.Num() != PreviousClassElements.Num())
		{
			if(NextClassElements.Num() > PreviousClassElements.Num())
			{
				/* SYMBIOTIC PRIORITY CHECK	- (Symbiotic class has edge-case priority over tri-elemental classes) */
				if(PreviousClassMajorElement == AdeptSymbioticElement &&
					ClassToSet->GetDjinnAmount(PreviousClassAvailability, AdeptSymbioticElement) >
					NextClass->GetDjinnAmount(NextClassAvailability, AdeptSymbioticElement))
						continue;
				
				ClassToSet = NextClass;
				continue;
			}
		}

		/* CLASS TIER - (Class Series order) */
		if(NextClass->ClassTier != ClassToSet->ClassTier)
		{
			if(NextClass->ClassTier > ClassToSet->ClassTier)
			{
				ClassToSet = NextClass;
				continue;
			}
		}

		/* DJINN PERCENTAGE - () */
		if(NextClassDjinnPercentage != PreviousClassDjinnPercentage)
		{
			if(NextClassDjinnPercentage > PreviousClassDjinnPercentage)
			{
				ClassToSet = NextClass;
				continue;
			}
		}
			
		
		if(NextClassMajorElement == AdeptUnrelatedElement && PreviousClassMajorElement != AdeptUnrelatedElement)
		{
			ClassToSet = NextClass;
			continue;
		}
		
		if(NextClassMajorElement == AdeptOppositeElement && PreviousClassMajorElement != AdeptUnrelatedElement)
		{
			ClassToSet = NextClass;
			continue;
		}

		if(NextClassMajorElement == AdeptSymbioticElement && PreviousClassMajorElement == Adept->BaseElement)
		{
			ClassToSet = NextClass;
			continue;
		}

		
		if(NextClass->GetDjinnAmount(NextClassAvailability) > ClassToSet->GetDjinnAmount(PreviousClassAvailability))
		{
			ClassToSet = NextClass;
			continue;
		}
	}

	
	return ClassToSet;
}


void AAdeptClassSeriesDatabase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


AAdeptClass* AAdeptClassSeriesDatabase::GetAdeptClass(AAdept* Adept)
{
	TArray<AAdeptClass*> PossibleClasses;
	for (TTuple<FString, TSubclassOf<AAdeptClassSeries>> Map : DatabaseMap)
	{
		if(!Map.Value.GetDefaultObject()->MeetsSeriesRequirement(Adept))
			continue;

		//Spawn/Get Class Series
		AAdeptClassSeries* ClassSeries = GetDatabaseItem(*Map.Key, &SpawnedClassSeries, &DatabaseMap);

		AAdeptClass* PossibleClass = ClassSeries->GetSeriesClass(Adept);
		
		if(PossibleClass != nullptr)
			PossibleClasses.Add(PossibleClass);
		
	}

	if(PossibleClasses.IsEmpty())
		return nullptr;

	AAdeptClass* ChosenAdeptClass = SortPossibleAdeptClasses(PossibleClasses, Adept);
	return ChosenAdeptClass;
}

