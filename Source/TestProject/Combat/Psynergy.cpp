// Fill out your copyright notice in the Description page of Project Settings.


#include "Psynergy.h"
// Sets default values
APsynergy::APsynergy()
{
	
}

void APsynergy::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &APsynergy::GetGameInstanceReferences, 0.5f, false, 0.5f);
	}
}

void APsynergy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APsynergy::GetGameInstanceReferences()
{
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		CombatTargeting = GameInstance->GetCombatTargeting();
	
	}
}

void APsynergy::Initialize(ACombatTargeting* CombatTargetPointer, AUnit* OwningUnit)
{
	CombatTargeting = CombatTargetPointer;
	SetOwningUnit(OwningUnit);
}

void APsynergy::SetOwningUnit(AUnit* OwningUnit)
{
	Unit = OwningUnit;
}


void APsynergy::SetTargets_Implementation(AUnit* OwningUnit)
{
	const FString Message = "Failed to set targets for " + Name;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, *Message);
}

void APsynergy::Execute_Implementation()
{
	const FString Message = "Failed to execute " + Name;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, *Message);
}
