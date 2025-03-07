// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdeptData.h"
#include "Engine/DataAsset.h"
#include "AdeptDatabaseData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GOLDENSUN_API UAdeptDatabaseData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UAdeptData>> PlayableAdepts;
};