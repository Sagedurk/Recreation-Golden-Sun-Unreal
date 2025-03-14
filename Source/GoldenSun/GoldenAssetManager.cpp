// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenAssetManager.h"

#include "CustomGameInstance.h"
#include "DataMaster.h"
#include "Tasks/Task.h"

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

	using namespace UE::Tasks;
	FTask LoadAssetTask = Launch(UE_SOURCE_LOCATION, [&AssetManager, &AdeptId, &Bundles] {AssetManager.LoadPrimaryAsset(AdeptId, Bundles);});

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("WAITING FOR ASSET TO LOAD"));

	LoadAssetTask.Wait(FTimespan::FromMilliseconds(3000));

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("WAITING FOR DATA TO BE ADDED TO PARTY"));
	
	FTask SubTask = Launch(UE_SOURCE_LOCATION, [&AssetManager, &PartyData, &AdeptId] {AssetManager.AddAdeptToParty(PartyData, AdeptId);});
	SubTask.Wait(FTimespan::FromMilliseconds(3000));

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("FINISHED WAITING"));
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

	_PartyData->PartyMemberData.Add(Adept);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ADEPT DATA ADDED"));
}

void UGoldenAssetManager::SetGameInstanceReference(UCustomGameInstance* _GameInstance)
{
	GameInstance = _GameInstance;
}
