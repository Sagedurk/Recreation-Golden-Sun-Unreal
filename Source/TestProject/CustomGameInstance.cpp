// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

#include "Databases/AdeptClassSeriesDatabase.h"


ACombatTargeting* UCustomGameInstance::GetCombatTargeting() const
{
	return CombatTargeting;
}


void UCustomGameInstance::TrySetCombatTargeting(ACombatTargeting* _CombatTargeting)
{
	if (CombatTargeting == nullptr)
		CombatTargeting = _CombatTargeting;
}

AMonsterDatabase* UCustomGameInstance::GetMonsterDatabase() const
{
	return MonsterDatabase;
}

void UCustomGameInstance::TrySetMonsterDatabase(AMonsterDatabase* _MonsterDatabase)
{
	if (MonsterDatabase == nullptr)
		MonsterDatabase = _MonsterDatabase;
}

AAdeptDatabase* UCustomGameInstance::GetAdeptDatabase() const
{
	return AdeptDatabase;
}

void UCustomGameInstance::TrySetAdeptDatabase(AAdeptDatabase* _AdeptDatabase)
{
	if (AdeptDatabase == nullptr)
		AdeptDatabase = _AdeptDatabase;
}

AAdeptClassSeriesDatabase* UCustomGameInstance::GetAdeptClassSeriesDatabase() const
{
	return AdeptClassSeriesDatabase;
}

void UCustomGameInstance::TrySetAdeptClassSeriesDatabase(AAdeptClassSeriesDatabase* _AdeptClassDatabase)
{
	if (AdeptClassSeriesDatabase == nullptr)
		AdeptClassSeriesDatabase = _AdeptClassDatabase;
}

APsynergyDatabase* UCustomGameInstance::GetPsynergyDatabase() const
{
	return PsynergyDatabase;
}

void UCustomGameInstance::TrySetPsynergyDatabase(APsynergyDatabase* _PsynergyDatabase)
{
	if (PsynergyDatabase == nullptr)
		PsynergyDatabase = _PsynergyDatabase;
}

ADjinniDatabase* UCustomGameInstance::GetDjinniDatabase() const
{
	return DjinniDatabase;
}

void UCustomGameInstance::TrySetDjinniDatabase(ADjinniDatabase* _DjinniDatabase)
{
	if (DjinniDatabase == nullptr)
		DjinniDatabase = _DjinniDatabase;
}

ACombatInitiator* UCustomGameInstance::GetCombatInitiator() const
{
	return CombatInitiator;
}

void UCustomGameInstance::TrySetCombatInitiator(ACombatInitiator* _CombatInitiator)
{
	if (CombatInitiator == nullptr)
		CombatInitiator = _CombatInitiator;
}

AParty* UCustomGameInstance::GetParty() const
{
	return Party;
}

void UCustomGameInstance::TrySetParty(AParty* _Party)
{
	if (Party == nullptr)
		Party = _Party;
}