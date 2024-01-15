// Fill out your copyright notice in the Description page of Project Settings.


#include "AdeptDatabase.h"

#include "TestProject/CustomGameInstance.h"


// Sets default values
AAdeptDatabase::AAdeptDatabase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdeptDatabase::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetAdeptDatabase(this);

		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &AAdeptDatabase::GetGameInstanceReferences, 0.5f, false, 0.5f);
	}

	DatabaseMap = ConvertDatabaseToMap(Database);
}

// Called every frame
void AAdeptDatabase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAdept* AAdeptDatabase::SpawnAdept(TSubclassOf<AAdept> AdeptToSpawn)
{
	return SpawnActor(AdeptToSpawn);
}

AAdept* AAdeptDatabase::SpawnAdept(FString AdeptName)
{	
	TSubclassOf<AAdept>* AdeptToSpawn = DatabaseMap.Find(AdeptName);

	if(AdeptToSpawn == nullptr)
		return nullptr;
	
	return SpawnActor(*AdeptToSpawn);
}

void AAdeptDatabase::GetGameInstanceReferences()
{
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		CombatTargeting = GameInstance->GetCombatTargeting();
		CombatInitiator = GameInstance->GetCombatInitiator();
	}
}

