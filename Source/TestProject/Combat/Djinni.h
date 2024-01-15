// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Djinni.generated.h"

class AAdept;
enum class EElementalType : uint8;

UENUM(BlueprintType)
enum class EDjinniState : uint8
{
	//Available for summon
	Set = 0		UMETA(DisplayName = "Set"),
	//Available for casting
	Standby = 1		UMETA(DisplayName = "Standby"),
	//Not available
	Recovery = 4		UMETA(DisplayName = "Recovery"),	
};


UCLASS()
class TESTPROJECT_API ADjinni : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADjinni();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EElementalType Element;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDjinniState State;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FUnitStats BaseStats;

	UPROPERTY(BlueprintReadOnly)
	AAdept* OwningAdept;
	//Set Targets
	//Execute Battle Effect
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetOwningAdept(AAdept* Adept);
};
