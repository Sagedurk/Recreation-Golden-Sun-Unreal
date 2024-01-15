// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestProject/CustomGameInstance.h"
#include "CombatInitiator.generated.h"

class ACombatTargeting;
class AUnit;

UCLASS()
class TESTPROJECT_API ACombatInitiator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatInitiator();


	UPROPERTY()
	ACombatTargeting* CombatTargeting;

	UPROPERTY()
	AParty* Party;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void RepositionTeam(TArray<AUnit*> Team, FVector TeamOrigin, FVector LocationOffset);
	void SetUnitLocation(AUnit* Unit, FVector Location);
	AUnit* SpawnUnit(TSubclassOf<AUnit> SubClassOfUnit, TArray<AUnit*>* Team);

private:
	void GetGameInstanceReferences();
	void InitiateCombat();
};
