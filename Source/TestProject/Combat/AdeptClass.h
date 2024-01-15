// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Psynergy.h"
#include "GameFramework/Actor.h"
#include "AdeptClass.generated.h"


struct FPsynergyAvailability;
class AAdept;
enum class EElementalType : uint8;

USTRUCT(BlueprintType)
struct FClassMultipliers
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HP = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PP = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Attack = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Defense = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Agility = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Luck = 1.0f;
};

USTRUCT(BlueprintType)
struct FClassDjinnRequirement
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EElementalType DjinnElement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DjinnAmount;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaximumDjinnAmount;
};

USTRUCT(BlueprintType)
struct FClassAvailability
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EElementalType AdeptElement;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FClassDjinnRequirement> DjinnRequirement;

	
};

UCLASS()
class TESTPROJECT_API AAdeptClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdeptClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString DisplayedClassName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ClassTier;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FClassAvailability> ClassAvailability;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FClassMultipliers StatMultipliers;
	

	UPROPERTY()
	TArray<FPsynergyAvailability> Psynergies;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FClassAvailability  TryGetAdeptAvailability(EElementalType AdeptElement);
	TArray<EElementalType> GetClassElements(FClassAvailability Availability);
	float GetPercentageMultiplierOfMaximumDjinn(FClassAvailability Availability, AAdept* Adept);
	int32 GetDjinnAmount(FClassAvailability Availability);
	int32 GetDjinnAmount(FClassAvailability Availability, EElementalType DjinnElement);
	EElementalType GetMajorElement(FClassAvailability Availability);
};
