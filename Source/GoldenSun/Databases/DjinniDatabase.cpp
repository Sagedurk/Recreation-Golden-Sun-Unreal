// Fill out your copyright notice in the Description page of Project Settings.


#include "DjinniDatabase.h"
#include "GoldenSun/CustomGameInstance.h"


void ADjinniDatabase::BeginPlay()
{
	Super::BeginPlay();

	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetDjinniDatabase(this);
	}
	
	DatabaseMap = ConvertDatabaseToMap(Database);
}

void ADjinniDatabase::GetGameInstanceReferences()
{
	Super::GetGameInstanceReferences();
	
}

ADjinni* ADjinniDatabase::GetDjinni(FString DjinniName)
{
	return GetDatabaseItem(DjinniName, &SpawnedDjinn, &DatabaseMap);
	
}

