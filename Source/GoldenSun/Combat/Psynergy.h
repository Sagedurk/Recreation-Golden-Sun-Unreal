// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTargeting.h"
#include "GoldenSun/CustomGameInstance.h"
#include "Psynergy.generated.h"

class AUnit;
enum class EElementalType : uint8;
enum class ETargetType : uint8;

UCLASS()
class GOLDENSUN_API APsynergy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APsynergy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Cost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementalType Element;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETargetType TargetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmountOfTargets;

	UPROPERTY(BlueprintReadOnly)
	AUnit* Unit;

	
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void GetGameInstanceReferences();

private:

	UPROPERTY()
	ACombatTargeting* CombatTargeting;
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Execute();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTargets(AUnit* OwningUnit);

	UFUNCTION(BlueprintCallable)
	void Initialize(ACombatTargeting* CombatTargetPointer, AUnit* OwningUnit);

	UFUNCTION(BlueprintCallable)
	void SetOwningUnit(AUnit* OwningUnit);
	
};
