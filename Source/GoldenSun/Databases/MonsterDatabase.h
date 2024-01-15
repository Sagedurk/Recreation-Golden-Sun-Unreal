// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbstractDatabase.h"
#include "GoldenSun/Combat/CombatInitiator.h"
#include "GoldenSun/Combat/CombatTargeting.h"
#include "GoldenSun/Combat/Monster.h"
#include "MonsterDatabase.generated.h"


UCLASS()
class GOLDENSUN_API AMonsterDatabase : public AAbstractDatabase//, public IDatabaseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterDatabase();

	UPROPERTY()
	TMap<FString, TSubclassOf<AMonster>> DatabaseMap;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AMonster>> Database;

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
	
	virtual void GetGameInstanceReferences() override;
	
	
	void SpawnMonsters(TArray<FString> MonsterNames);
	
private:
	
	//void ConvertDatabaseToMap();
	void SpawnMonsters(TArray<TSubclassOf<AMonster>*> Monsters);
};
