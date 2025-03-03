// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "DataMaster.h"
#include "DataMaster.h"
#include "Engine/GameInstance.h"
#include "Combat/CombatTargeting.h"
#include "CustomGameInstance.generated.h"

class UGoldenAssetManager;
class AAdeptDatabase;
class AAdeptClassSeriesDatabase;
class ADjinniDatabase;
class AMonsterDatabase;
class AParty;
class ACombatInitiator;
class APsynergyDatabase;
/**
 * 
 */
UCLASS()
class GOLDENSUN_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	ACombatTargeting* GetCombatTargeting() const;

	void TrySetCombatTargeting(ACombatTargeting* _CombatTargeting);

	UFUNCTION(BlueprintCallable)
	AMonsterDatabase* GetMonsterDatabase() const;

	void TrySetMonsterDatabase(AMonsterDatabase* _MonsterDatabase);

	UFUNCTION(BlueprintCallable)
	AAdeptDatabase* GetAdeptDatabase() const;

	void TrySetAdeptDatabase(AAdeptDatabase* _AdeptDatabase);

	UFUNCTION(BlueprintCallable)
	AAdeptClassSeriesDatabase* GetAdeptClassSeriesDatabase() const;

	void TrySetAdeptClassSeriesDatabase(AAdeptClassSeriesDatabase* _AdeptClassDatabase);
	
	UFUNCTION(BlueprintCallable)
	APsynergyDatabase* GetPsynergyDatabase() const;

	void TrySetPsynergyDatabase(APsynergyDatabase* _PsynergyDatabase);

	UFUNCTION(BlueprintCallable)
	ADjinniDatabase* GetDjinniDatabase() const;

	void TrySetDjinniDatabase(ADjinniDatabase* _DjinniDatabase);

	UFUNCTION(BlueprintCallable)
	ACombatInitiator* GetCombatInitiator() const;

	void TrySetCombatInitiator(ACombatInitiator* _CombatInitiator);

	UFUNCTION(BlueprintCallable)
	AParty* GetParty() const;

	UFUNCTION(BlueprintCallable)
	UPartyData* GetPartyData() const;
	
private:

	UPROPERTY()
	UGoldenAssetManager* AssetManager;
	
	UPROPERTY()
	ACombatTargeting* CombatTargeting;

	UPROPERTY()
	AMonsterDatabase* MonsterDatabase;
	
	UPROPERTY()
	AAdeptDatabase* AdeptDatabase;

	UPROPERTY()
	AAdeptClassSeriesDatabase* AdeptClassSeriesDatabase;

	UPROPERTY()
	APsynergyDatabase* PsynergyDatabase;
	
	UPROPERTY()
	ADjinniDatabase* DjinniDatabase;
	
	UPROPERTY()
	ACombatInitiator* CombatInitiator;
	
	UPROPERTY()
	AParty* Party;
	
	UPROPERTY()
	UPartyData* PartyData;

	UPROPERTY()
	UAdeptDatabaseData* AdeptDatabaseData;
	
};
