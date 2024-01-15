// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Psynergy.h"
#include "GameFramework/Actor.h"
#include "GoldenSun/Databases/AbstractDatabase.h"
#include "AdeptClassSeries.generated.h"

class AAdeptClass;

USTRUCT()
struct FPsynergyAvailability
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int LevelCheck;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APsynergy> Psynergy;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAdeptClass> ClassRequirement;
	
};

USTRUCT()
struct FSeriesAvailability
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EElementalType AdeptElement;
	UPROPERTY(EditDefaultsOnly)
	TArray<EElementalType> MajorDjinnElements;
	
};

UCLASS()
class GOLDENSUN_API AAdeptClassSeries : public AAbstractDatabase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdeptClassSeries();

	AAdeptClass* GetSeriesClass(AAdept* Adept);

	bool MeetsSeriesRequirement(AAdept* Adept);
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AAdeptClass>> Classes;
	UPROPERTY(EditDefaultsOnly)
	TArray<FPsynergyAvailability> Psynergies;
	UPROPERTY(EditDefaultsOnly)
	TArray<FSeriesAvailability> Requirements;
	

	UPROPERTY()
	TMap<FString, TSubclassOf<AAdeptClass>> DatabaseMap;

	UPROPERTY()
	TMap<FString, AAdeptClass*> SpawnedClasses;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetGameInstanceReferences() override;
	bool MeetsDjinnRequirement(AAdept* Adept, FClassAvailability ClassAvailability);

	void PopulateClassPsynergies(AAdeptClass* AdeptClass);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
