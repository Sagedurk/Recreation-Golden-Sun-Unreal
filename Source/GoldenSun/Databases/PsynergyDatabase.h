// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractDatabase.h"
#include "GoldenSun/Combat/Psynergy.h"
#include "PsynergyDatabase.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENSUN_API APsynergyDatabase : public AAbstractDatabase
{
	GENERATED_BODY()

		
public:	
	// Sets default values for this actor's properties
	APsynergyDatabase();


	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<APsynergy>> Database;

	UPROPERTY()
	TMap<FString, TSubclassOf<APsynergy>> DatabaseMap;

	UPROPERTY()
	TMap<FString, APsynergy*> SpawnedPsynergies;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void GetGameInstanceReferences() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APsynergy* GetPsynergy(FString PsynergyName);
	
};
