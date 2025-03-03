// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatInitiator.h"

#include "Unit.h"
#include "GoldenSun/CustomGameInstance.h"
#include "GoldenSun/Party.h"

class UCustomGameInstance;
// Sets default values
ACombatInitiator::ACombatInitiator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatInitiator::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetCombatInitiator(this);
		
		FTimerHandle CombatInitTimer; 
		GameInstance->TimerManager->SetTimer(CombatInitTimer, this, &ACombatInitiator::GetGameInstanceReferences, 0.5f, false, 0.5f);
	
	}
	
	
}

// Called every frame
void ACombatInitiator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombatInitiator::RepositionTeam(TArray<AUnit*> Team, FVector TeamOrigin, FVector LocationOffset)
{
	FVector UnitLocation = TeamOrigin - LocationOffset * (Team.Num() / 2.0f) + LocationOffset / 2;
	for (size_t i = 0; i < Team.Num(); i++)
	{
		SetUnitLocation(Team[i], UnitLocation);
		UnitLocation += LocationOffset;
	}	
}


void ACombatInitiator::SetUnitLocation(AUnit* Unit, FVector Location)
{
	Unit->SetActorLocation(Location);
}

AUnit* ACombatInitiator::SpawnUnit(TSubclassOf<AUnit> SubClassOfUnit, TArray<AUnit*>* Team)
{
	AUnit* SpawnedUnit = GetWorld()->SpawnActor<AUnit>(SubClassOfUnit);
	Team->Add(SpawnedUnit);
	return SpawnedUnit;
}

void ACombatInitiator::GetGameInstanceReferences()
{
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		CombatTargeting = GameInstance->GetCombatTargeting();
		PartyData = GameInstance->GetPartyData();
		InitiateCombat();
	}

}

void ACombatInitiator::InitiateCombat()
{
	for (size_t i = 0; i < PartyData->PartyMembers.Num(); i++)
	{
		if(i >= MaxAdepts)
			break;

		CombatTargeting->AllyTeam.Add(AdeptTemplates[i]);
		SetAdeptData(AdeptTemplates[i], PartyData->PartyData[i]);
	}

	const int AdeptTemplatesToRemove = AdeptTemplates.Num() - PartyData->PartyMembers.Num();

	if(AdeptTemplatesToRemove > 0)
	{
		for (size_t i = 0; i < AdeptTemplatesToRemove; i++)
		{
			AAdept* Adept = AdeptTemplates.Pop();
			Adept->Destroy();
		}
	}

	RepositionTeam(CombatTargeting->AllyTeam, FVector(-150, 0, 0), FVector(0, 100, 0));
	
}

void ACombatInitiator::SetAdeptData(AAdept* AdeptObject, const UAdeptData* AdeptData)
{
	AdeptObject->Name = AdeptData->Name;
	AdeptObject->Portrait = AdeptData->Portrait;
	AdeptObject->CombatMesh = AdeptData->CombatMesh;
}



