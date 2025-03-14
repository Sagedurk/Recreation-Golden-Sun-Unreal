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

	UPROPERTY(BlueprintReadWrite)
	TArray<UAdeptData*> PartyMemberData;

	FName GetCurrentPartyMemberName();
	
	UFUNCTION(BlueprintCallable)
	int GetCurrentPartyMemberIndex();

	UFUNCTION(BlueprintCallable)
	void LoadPartyData(TArray<FName> Bundles);

	UFUNCTION(BlueprintCallable)
	void UnloadPartyData();
	
private:

	UPROPERTY()
	UGoldenAssetManager* AssetManager;

	int CurrentPartyMemberIndex;
};
