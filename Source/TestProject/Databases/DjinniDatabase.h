// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractDatabase.h"
#include "TestProject/Combat/Djinni.h"
#include "DjinniDatabase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ADjinniDatabase : public AAbstractDatabase
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ADjinni>> Database;

	UPROPERTY()
	TMap<FString, TSubclassOf<ADjinni>> DatabaseMap;

	UPROPERTY()
	TMap<FString, ADjinni*> SpawnedDjinn;

	
	ADjinni* GetDjinni(FString DjinniName);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void GetGameInstanceReferences() override;
};
