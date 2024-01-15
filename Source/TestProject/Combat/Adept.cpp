// Fill out your copyright notice in the Description page of Project Settings.


#include "Adept.h"

#include "AdeptClassSeries.h"
#include "Psynergy.h"
#include "TestProject/CustomGameInstance.h"
#include "TestProject/Databases/AdeptClassSeriesDatabase.h"
#include "TestProject/Databases/PsynergyDatabase.h"

void AAdept::BeginPlay()
{
	Super::BeginPlay();

	InitializeStats(&TotalStats);
	InitializeStats(&CurrentStats);
	
	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		PsynergyDatabase = GameInstance->GetPsynergyDatabase();
		SpawnPsynergies();

		DjinniDatabase = GameInstance->GetDjinniDatabase();
		SpawnDjinn();

		AdeptClassDatabase = GameInstance->GetAdeptClassSeriesDatabase();
		UpdateAdeptClass();
	}
}

void AAdept::SpawnPsynergies()
{
	for (size_t i = 0; i < Psynergies.Num(); i++)
	{	
		TSubclassOf<APsynergy> Psynergy = Psynergies[i];

		FString PsynergyName = Psynergy->GetName();
		PsynergyName.RemoveFromStart(PsynergyDatabase->NamingConventionPrefix);
		PsynergyName.RemoveFromEnd("_C");
		
		APsynergy* SpawnedPsynergy = GetPsynergy(PsynergyName);

		if(SpawnedPsynergies.Contains(SpawnedPsynergy))
			continue;

		SpawnedPsynergies.Add(SpawnedPsynergy);
	}	
}

void AAdept::SpawnDjinn()
{
	for (size_t i = 0; i < Djinn.Num(); i++)
	{	
		TSubclassOf<ADjinni> Djinni = Djinn[i];

		FString DjinniName = Djinni->GetName();
		DjinniName.RemoveFromStart(DjinniDatabase->NamingConventionPrefix);
		DjinniName.RemoveFromEnd("_C");
		
		ADjinni* SpawnedDjinni = GetDjinni(DjinniName);

		if(SpawnedDjinn.Contains(SpawnedDjinni))
			continue;

		SpawnedDjinn.Add(SpawnedDjinni);
		SpawnedDjinni->SetOwningAdept(this);
	}	
}

void AAdept::UpdatePsynergy()
{
	Psynergies.Empty();
	SpawnedPsynergies.Empty();

	if(AdeptClass != nullptr)
	{
		for (FPsynergyAvailability Psynergy : AdeptClass->Psynergies)
		{
			if(Level < Psynergy.LevelCheck)
				continue;

			Psynergies.Add(Psynergy.Psynergy);
		}
	}

	//TODO: Add Psynergy originating from equipped items
	SpawnPsynergies();
}

void AAdept::UpdateAdeptClass()
{
	//TODO: Update Psynergy here
	AdeptClass = AdeptClassDatabase->GetAdeptClass(this);
	UpdatePsynergy();
	UpdateStats();
	
}

void AAdept::UpdateStats()
{
	/* Calculate Current Stat Percentages */
	float CurrentPercentageHP = static_cast<float> (CurrentStats.HP) /static_cast<float> (TotalStats.HP);
	float CurrentPercentagePP = static_cast<float> (CurrentStats.PP) /static_cast<float> (TotalStats.PP);
	float CurrentPercentageAttack = static_cast<float> (CurrentStats.Attack) /static_cast<float> (TotalStats.Attack);
	float CurrentPercentageDefense = static_cast<float> (CurrentStats.Defense) /static_cast<float> (TotalStats.Defense);
	float CurrentPercentageAgility = static_cast<float> (CurrentStats.Agility) /static_cast<float> (TotalStats.Agility);
	float CurrentPercentageLuck = static_cast<float> (CurrentStats.Luck) /static_cast<float> (TotalStats.Luck);
	
	/* Update Total Stats */
	TotalStats.HP = BaseStats.HP * AdeptClass->StatMultipliers.HP;
	TotalStats.PP = BaseStats.PP * AdeptClass->StatMultipliers.PP;
	TotalStats.Attack = BaseStats.Attack * AdeptClass->StatMultipliers.Attack;
	TotalStats.Defense = BaseStats.Defense * AdeptClass->StatMultipliers.Defense;
	TotalStats.Agility = BaseStats.Agility * AdeptClass->StatMultipliers.Agility;
	TotalStats.Luck = BaseStats.Luck * AdeptClass->StatMultipliers.Luck;
	
	
	/* Update Current Stats */
	CurrentStats.HP = TotalStats.HP * CurrentPercentageHP;
	CurrentStats.PP = TotalStats.PP * CurrentPercentagePP;
	CurrentStats.Attack = TotalStats.Attack * CurrentPercentageAttack;
	CurrentStats.Defense = TotalStats.Defense * CurrentPercentageDefense;
	CurrentStats.Agility = TotalStats.Agility * CurrentPercentageAgility;
	CurrentStats.Luck = TotalStats.Luck * CurrentPercentageLuck;
}

void AAdept::InitializeStats(FUnitStats* StatBlock)
{
	StatBlock->HP = BaseStats.HP;
	StatBlock->PP = BaseStats.PP;
	StatBlock->Attack = BaseStats.Attack;
	StatBlock->Defense = BaseStats.Defense;
	StatBlock->Agility = BaseStats.Agility;
	StatBlock->Luck = BaseStats.Luck;
}


TArray<APsynergy*> AAdept::GetPsynergies()
{
	TArray<APsynergy*> PsynergyArray;

	for (size_t i = 0; i < SpawnedPsynergies.Num(); i++)
	{
			PsynergyArray.Add(SpawnedPsynergies[i]);
	}

	return PsynergyArray;
}

TArray<ADjinni*> AAdept::GetDjinn()
{
	TArray<ADjinni*> DjinnArray;

	for (size_t i = 0; i < SpawnedDjinn.Num(); i++)
	{
		DjinnArray.Add(SpawnedDjinn[i]);
	}

	return DjinnArray;
}

int32 AAdept::GetDjinnAmount(EElementalType DjinnElement)
{
	int32 DjinnAmount = 0;
	for (size_t i = 0; i < SpawnedDjinn.Num(); i++)
	{
		ADjinni* Djinni = SpawnedDjinn[i];

		if(Djinni->Element != DjinnElement)
			continue;

		DjinnAmount++;
	}

	return DjinnAmount;
}

int32 AAdept::GetDjinnAmount(EElementalType DjinnElement, EDjinniState State)
{
	int32 DjinnAmount = 0;
	for (size_t i = 0; i < SpawnedDjinn.Num(); i++)
	{
		ADjinni* Djinni = SpawnedDjinn[i];

		if(Djinni->Element != DjinnElement || Djinni->State != State)
			continue;

		DjinnAmount++;
	}

	return DjinnAmount;
}

APsynergy* AAdept::GetPsynergy(FString PsynergyName)
{
	return PsynergyDatabase->GetPsynergy(PsynergyName);
}

ADjinni* AAdept::GetDjinni(FString DjinniName)
{
	return DjinniDatabase->GetDjinni(DjinniName);
}

AAdeptClass* AAdept::GetNextClass(ADjinni* Djinni)
{
	if(Djinni->State == EDjinniState::Set)
	{
		Djinni->State = EDjinniState::Standby;
	}
	else if(Djinni->State == EDjinniState::Standby)
	{
		Djinni->State = EDjinniState::Set;
	}
	
	AAdeptClass* NextClass = AdeptClassDatabase->GetAdeptClass(this);

	
	if(Djinni->State == EDjinniState::Set)
	{
		Djinni->State = EDjinniState::Standby;
	}
	
	else if(Djinni->State == EDjinniState::Standby)
	{
		Djinni->State = EDjinniState::Set;
	}
	
		
	return NextClass;
}