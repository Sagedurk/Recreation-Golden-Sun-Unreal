// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "MajorTargetSelector.h"
#include "MinorTargetSelector.h"
#include "Monster.h"
#include "GameFramework/Actor.h"
#include "CombatTargeting.generated.h"

class AParty;

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	Single,
	Multiple,
	All,
};

UENUM(BlueprintType)
enum class ECombatTargetType : uint8
{
	Ally = 0		UMETA(DisplayName = "Ally Team"),
	Enemy = 1		UMETA(DisplayName = "Enemy Team"),
};

UCLASS()
class GOLDENSUN_API ACombatTargeting : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatTargeting();

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<AMajorTargetSelector> MajorSelectorBP;
	
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<AMinorTargetSelector> MinorSelectorBP;

	UPROPERTY(EditAnywhere)
	TArray<AUnit*> AllyTeam;

	UPROPERTY(EditAnywhere)
	TArray<AUnit*> EnemyTeam;
	
	TArray<AUnit*>* UnitTeam;

	UPROPERTY()
	TMap<AUnit*, int> TargetMap;

	UPROPERTY(BlueprintReadWrite)
	AUnit* CurrentUnit;
	
	UPROPERTY()
	TArray<AMajorTargetSelector*> MajorSelectors;
	
	UPROPERTY()
	TArray<AMinorTargetSelector*> MinorSelectors;

	UPROPERTY(BlueprintReadWrite)
	int MinorTargetAmount = 0;

	UPROPERTY()
	AParty* Party;
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BeginTargeting(AUnit* Unit, ECombatTargetType TargetTeam);
	
	UFUNCTION(BlueprintCallable)
	void Return();
	
	void FinishTargeting();

	UFUNCTION(BlueprintNativeEvent)
	void ProceedToNextPartyMember();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteCombatTurn();

	void NextTarget();

	void PreviousTarget();

	TArray<AUnit*>* GetAlliedTeam(AUnit* Unit);
	
	TArray<AUnit*>* GetOpposingTeam(AUnit* Unit);
private:

	void GetGameInstanceReferences();

	int GetTargetIndex();

	void CreateTargetMap();

	AUnit* GetMiddleUnit(TArray<AUnit*> units);

	void Reset();

	/** Set Target */

	void SetTargets(AUnit* MainTarget);

	void SetTarget(AUnit* Unit, AUnit* Target);

	void SetTargetEnemy(AUnit* Unit);

	void SetTargetSelf(AUnit* Unit);

	void TrySetMinorTargets();


	/** Spawn Selectors */

	void SpawnTargetSelectors();

	void SpawnMajorTargetSelectors();

	void SpawnMinorTargetSelectors();


	/** Destroy Selectors */

	void DestroyTargetSelectors();

	void DestroyMajorTargetSelectors();

	void DestroyMinorTargetSelectors();


	/** Set Selectors */
	
	void SetTargetSelectors();

	void SetMajorTargetSelectors();
	
	void SetMinorTargetSelectors();

	void SetMajorTargetSelector(AMajorTargetSelector* Selector, AUnit* Target);
	
	void SetMinorTargetSelector(AMinorTargetSelector* Selector, AUnit* Target);


	/** Hide Selectors */
	
	void HideMajorSelector(AMajorTargetSelector* Selector);

	void HideMinorSelector(AMinorTargetSelector* Selector);

};
