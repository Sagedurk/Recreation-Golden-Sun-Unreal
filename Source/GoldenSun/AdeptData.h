// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element.h"
#include "Engine/DataAsset.h"
#include "AdeptData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GOLDENSUN_API UAdeptData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, AssetRegistrySearchable)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementalType BaseElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AssetBundles = "Combat"))
	USkeletalMesh* CombatMesh;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};



