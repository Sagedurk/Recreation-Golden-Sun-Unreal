// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenAssetManager.h"

#include "CustomGameInstance.h"
#include "DataMaster.h"

const FPrimaryAssetType UGoldenAssetManager::DataMasterType = TEXT("MasterAsset");
const FPrimaryAssetType UGoldenAssetManager::AdeptType = TEXT("Adept");

void UGoldenAssetManager::SetPartyData()
{
	UGoldenAssetManager& AssetManager = Get();

	TArray<FPrimaryAssetId> DataMasterIdList;
	AssetManager.GetPrimaryAssetIdList(DataMasterType, DataMasterIdList);

	TArray<FName> Bundles;

	FPrimaryAssetId DataMasterId = DataMasterIdList[0];
	AssetManager.LoadPrimaryAsset(DataMasterId, Bundles, FStreamableDelegate::CreateUObject(&AssetManager, &UGoldenAssetManager::Callback, DataMasterId));
	
}

void UGoldenAssetManager::SetAdeptDatabaseData()
{
	UGoldenAssetManager& AssetManager = Get();

	TArray<FPrimaryAssetId> DataMasterIdList;
	AssetManager.GetPrimaryAssetIdList(DataMasterType, DataMasterIdList);

	TArray<FName> Bundles;

	FPrimaryAssetId DataMasterId = DataMasterIdList[0];
	AssetManager.LoadPrimaryAsset(DataMasterId, Bundles, FStreamableDelegate::CreateUObject(&AssetManager, &UGoldenAssetManager::DatabaseCallback, DataMasterId));
}

void UGoldenAssetManager::LoadAdeptData(UPartyData* PartyData, FName AdeptName, const TArray<FName>& Bundles)
{
	UGoldenAssetManager& AssetManager = Get();
	FPrimaryAssetId AdeptId = FPrimaryAssetId(AdeptType, AdeptName);
	AssetManager.LoadPrimaryAsset(AdeptId, Bundles, FStreamableDelegate::CreateUObject(&AssetManager, &UGoldenAssetManager::AddAdeptToParty, PartyData, AdeptId));
}

void UGoldenAssetManager::Callback(FPrimaryAssetId DataMasterId)
{
	UDataMaster* DataMaster = GetPrimaryAssetObject<UDataMaster>(DataMasterId);

	if(!DataMaster)
		return;

	PartyData = DataMaster->Party;
}

void UGoldenAssetManager::DatabaseCallback(FPrimaryAssetId DataMasterId)
{
	UDataMaster* DataMaster = GetPrimaryAssetObject<UDataMaster>(DataMasterId);
	
	if(!DataMaster)
		return;

	AdeptDatabaseData = DataMaster->AdeptDatabase;
}

UGoldenAssetManager& UGoldenAssetManager::Get()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	UGoldenAssetManager& GoldenAssetManager = static_cast<UGoldenAssetManager&>(AssetManager);
	return GoldenAssetManager;
}

void UGoldenAssetManager::AddAdeptToParty(UPartyData* _PartyData, FPrimaryAssetId AdeptId)
{
	UAdeptData* Adept = GetPrimaryAssetObject<UAdeptData>(AdeptId);

	if(!Adept || !_PartyData)
		return;

	_PartyData->PartyData.Add(Adept);
}

void UGoldenAssetManager::SetGameInstanceReference(UCustomGameInstance* _GameInstance)
{
	GameInstance = _GameInstance;
}
