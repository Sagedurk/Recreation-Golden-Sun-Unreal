// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Djinni.h"
#include "GoldenSun/Databases/DjinniDatabase.h"
#include "Adept.generated.h"

class AAdeptClassSeriesDatabase;
class AAdeptClass;
class APsynergyDatabase;
//enum class EElementalType : uint8;



UCLASS()
class GOLDENSUN_API AAdept : public AUnit
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementalType BaseElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Portrait;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Level;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Experience;
	
	UPROPERTY(BlueprintReadOnly)
	AAdeptClass* AdeptClass;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUnitStats BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUnitStats CurrentStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUnitStats TotalStats;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APsynergy>> Psynergies;

	UPROPERTY(BlueprintReadWrite)
	TArray<APsynergy*> SpawnedPsynergies;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ADjinni>> Djinn;

	UPROPERTY(BlueprintReadWrite)
	TArray<ADjinni*> SpawnedDjinn;
	//UPROPERTY(EditAnywhere)
	//TArray<TSubclassOf<AItem>> Inventory;		//Alt name: Items
	
	/* 
	* HP - Current/Total
	*	Base HP
	* PP - Current/Total
	*	Base PP
	* Attack
	*	Base Attack
	* Defense
	*	Base Defense
	* Agility
	*	Base Agility
	* Luck
	*	Base Luck
	*
	* Status Effect
	*
	* Elemental - Venus, Mercury, Mars, Jupiter
	*		Djinn - Set/Total
	*		Level
	*		Power
	*		Resistance
	* 
	*/


	
protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY()
	APsynergyDatabase* PsynergyDatabase;

	UPROPERTY()
	ADjinniDatabase* DjinniDatabase;

	UPROPERTY()
	AAdeptClassSeriesDatabase* AdeptClassDatabase;

	void GetGameInstanceReferences();
	void SpawnPsynergies();
	void SpawnDjinn();
	void UpdatePsynergy();

public:


	UFUNCTION(BlueprintCallable)
	void UpdateAdeptClass();

	void UpdateStats();
	void InitializeStats(FUnitStats* StatBlock);

	UFUNCTION(BlueprintCallable)
	FUnitStats CalculateNewStats(ADjinni* Djinni, AAdeptClass* ClassPreview);
	FUnitStats SubtractStats(FUnitStats Minuend, FUnitStats Subtrahend);
	FUnitStats AddStats(FUnitStats Addend, FUnitStats Addend2);

	UFUNCTION(BlueprintCallable)
	TArray<APsynergy*> GetPsynergies();

	UFUNCTION(BlueprintCallable)
	TArray<ADjinni*> GetDjinn();

	int32 GetDjinnAmount(EElementalType DjinnElement);
	int32 GetDjinnAmount(EDjinniState State);
	int32 GetDjinnAmount(EElementalType DjinnElement, EDjinniState State);
	
	UFUNCTION(BlueprintCallable)
	APsynergy* GetPsynergy(FString PsynergyName);
	ADjinni* GetDjinni(FString PsynergyName);

	UFUNCTION(BlueprintCallable)
	AAdeptClass* GetNextClass(ADjinni* Djinni);
};

