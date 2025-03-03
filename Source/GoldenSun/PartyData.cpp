// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyData.h"

#include "GoldenAssetManager.h"

void UPartyData::LoadPartyData(TArray<FName> Bundles)
{
	AssetManager = &UGoldenAssetManager::Get();
	UnloadPartyData();
	
	for (size_t i = 0; i < PartyMembers.Num(); i++)
	{
		FName CurrentAdept = PartyMembers[i];
		
		AssetManager->LoadAdeptData(this, CurrentAdept, Bundles);
	}
}

void UPartyData::UnloadPartyData()
{
	for (size_t i = 0; i < PartyData.Num(); i++)
	{
		if(PartyData[i] == nullptr)
			continue;
			
		FPrimaryAssetId AdeptAssetId = FPrimaryAssetId(AssetManager->AdeptType, PartyData[i]->Name);
		AssetManager->UnloadPrimaryAsset(AdeptAssetId);
	}

	PartyData.Empty();
}
