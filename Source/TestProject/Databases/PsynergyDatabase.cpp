// Fill out your copyright notice in the Description page of Project Settings.


#include "PsynergyDatabase.h"

APsynergyDatabase::APsynergyDatabase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APsynergyDatabase::BeginPlay()
{
	Super::BeginPlay();

	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetPsynergyDatabase(this);
	}
	
	DatabaseMap = ConvertDatabaseToMap(Database);
}

void APsynergyDatabase::GetGameInstanceReferences()
{
	Super::GetGameInstanceReferences();

	
}

void APsynergyDatabase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

APsynergy* APsynergyDatabase::GetPsynergy(FString PsynergyName)
{
	return GetDatabaseItem(PsynergyName, &SpawnedPsynergies, &DatabaseMap);
}
