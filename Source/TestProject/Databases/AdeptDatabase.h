// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractDatabase.h"
#include "GameFramework/Actor.h"
#include "TestProject/Combat/Adept.h"
#include "TestProject/Combat/CombatInitiator.h"
#include "TestProject/Combat/CombatTargeting.h"
#include "AdeptDatabase.generated.h"

UCLASS()
class TESTPROJECT_API AAdeptDatabase : public AAbstractDatabase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdeptDatabase();

	UPROPERTY()
	TMap<FString, TSubclassOf<AAdept>> DatabaseMap;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AAdept>> Database;

	UPROPERTY()
	ACombatTargeting* CombatTargeting;

	UPROPERTY()
	ACombatInitiator* CombatInitiator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAdept* SpawnAdept(TSubclassOf<AAdept> AdeptToSpawn);
	AAdept* SpawnAdept(FString AdeptName);
	virtual void GetGameInstanceReferences() override;
};
