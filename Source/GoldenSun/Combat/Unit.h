// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

class APsynergy;

USTRUCT(Blueprintable)
struct FUnitStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Agility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Luck;
};

UCLASS()
class GOLDENSUN_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	UPROPERTY(EditAnywhere)
	FString UnitName = "";

	UPROPERTY()
	AUnit* CurrentTarget;	//Move to CombatTargeting

	TArray<AUnit*> MajorTargets;
	TArray<AUnit*> MinorTargets;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SelectPsynergy(APsynergy Psynergy);
};
