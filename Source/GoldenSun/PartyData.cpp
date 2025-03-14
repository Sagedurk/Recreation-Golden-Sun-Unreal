// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyData.h"

#include "GoldenAssetManager.h"

FName UPartyData::GetCurrentPartyMemberName()
{
	return PartyMembers[CurrentPartyMemberIndex];
}

int UPartyData::GetCurrentPartyMemberIndex()
{
	FMathf::Clamp(CurrentPartyMemberIndex, 0, PartyMembers.Num() - 1);
	return CurrentPartyMemberIndex;
}

//TODO: Make function wait for Asset Manager to finish loading Adept Data
//TODO: Research BlueprintAsyncActionBase
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
	for (size_t i = 0; i < PartyMemberData.Num(); i++)
	{
		if(PartyMemberData[i] == nullptr)
			continue;
			
		FPrimaryAssetId AdeptAssetId = FPrimaryAssetId(AssetManager->AdeptType, PartyMemberData[i]->Name);
		AssetManager->UnloadPrimaryAsset(AdeptAssetId);
	}

	PartyMemberData.Empty();
}
