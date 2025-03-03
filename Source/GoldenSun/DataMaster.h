// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdeptDatabaseData.h"
#include "PartyData.h"
#include "Engine/DataAsset.h"
#include "DataMaster.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENSUN_API UDataMaster : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable)
	UAdeptDatabaseData* AdeptDatabase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, AssetRegistrySearchable)
	UPartyData* Party;

	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("MasterAsset", GetFName());
	};
};
