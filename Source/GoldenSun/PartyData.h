// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PartyData.generated.h"

class UGoldenAssetManager;
class UAdeptData;
/**
 * 
 */
UCLASS(BlueprintType)
class GOLDENSUN_API UPartyData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> PartyMembers;

	UPROPERTY(BlueprintReadOnly)
	TArray<UAdeptData*> PartyData;

	void LoadPartyData(TArray<FName> Bundles);

private:
	void UnloadPartyData();

	UPROPERTY()
	UGoldenAssetManager* AssetManager;
};
