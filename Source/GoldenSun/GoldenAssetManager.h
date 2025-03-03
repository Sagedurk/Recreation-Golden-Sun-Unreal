// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdeptDatabaseData.h"
#include "CustomGameInstance.h"
#include "PartyData.h"
#include "Engine/AssetManager.h"
#include "GoldenAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENSUN_API UGoldenAssetManager : public UAssetManager
{
	GENERATED_BODY()


public:
	void SetPartyData();
	void SetAdeptDatabaseData();
	static void LoadAdeptData(UPartyData* PartyData, FName AdeptName, const TArray<FName>& Bundles = TArray<FName>());
	void Callback(FPrimaryAssetId DataMasterId);
	void DatabaseCallback(FPrimaryAssetId DataMasterId);
	void AddAdeptToParty(UPartyData* _PartyData, FPrimaryAssetId AdeptId);
	void SetGameInstanceReference(UCustomGameInstance* _GameInstance);
	static UGoldenAssetManager& Get();
	
private:
	


public:
	static const FPrimaryAssetType DataMasterType;
	static const FPrimaryAssetType AdeptType;

	UPROPERTY()
	UPartyData* PartyData;
	
	UPROPERTY()
	UAdeptDatabaseData* AdeptDatabaseData;

	UPROPERTY()
	UCustomGameInstance* GameInstance;
};
