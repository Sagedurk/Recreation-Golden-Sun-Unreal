// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractDatabase.h"
#include "TestProject/Combat/Adept.h"
#include "TestProject/Combat/AdeptClass.h"
#include "AdeptClassSeriesDatabase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AAdeptClassSeriesDatabase : public AAbstractDatabase
{
	GENERATED_BODY()
			
public:	
	// Sets default values for this actor's properties
	AAdeptClassSeriesDatabase();


	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AAdeptClassSeries>> Database;

	UPROPERTY()
	TMap<FString, TSubclassOf<AAdeptClassSeries>> DatabaseMap;

	UPROPERTY()
	TMap<FString, AAdeptClassSeries*> SpawnedClassSeries;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void GetGameInstanceReferences() override;
	bool MeetsDjinnRequirement(AAdept* Adept, FClassAvailability ClassAvailability);
	AAdeptClass* SortPossibleAdeptClasses(TArray<AAdeptClass*> PossibleClasses, AAdept* Adept);

	//FClassAvailability CompareClassAvailabilities(EElementalType AdeptElement, AAdeptClass* Class1, AAdeptClass* Class2);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAdeptClass* GetAdeptClass(AAdept* Adept);

};
