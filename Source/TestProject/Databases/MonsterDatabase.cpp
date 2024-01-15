// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDatabase.h"

#include "TestProject/CustomGameInstance.h"

// Sets default values
AMonsterDatabase::AMonsterDatabase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonsterDatabase::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetMonsterDatabase(this);

		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &AMonsterDatabase::GetGameInstanceReferences, 0.5f, false, 0.5f);
	}

	DatabaseMap = ConvertDatabaseToMap(Database);

}

// Called every frame
void AMonsterDatabase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterDatabase::GetGameInstanceReferences()
{
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		CombatTargeting = GameInstance->GetCombatTargeting();
		CombatInitiator = GameInstance->GetCombatInitiator();
	}

	//TArray<FString> Monsters = {"Skeleton", "ArmoredRat", "Ooze", "LizardKing", "Mimic"}; 
	TArray<FString> Monsters = {"Skeleton", "ArmoredRat", "LizardKing", "Mimic"}; 
	SpawnMonsters(Monsters);
}


void AMonsterDatabase::SpawnMonsters(TArray<TSubclassOf<AMonster>*> Monsters)
{
	FVector TeamOrigin = FVector(150, 0,50);
	const FVector SpawnOffset = FVector::RightVector * 100;
	
	for (size_t i = 0; i < Monsters.Num(); i++)
	{
		TSubclassOf<AMonster> Monster = *Monsters[i];

		CombatInitiator->SpawnUnit(Monster, &CombatTargeting->EnemyTeam);
	}

	CombatInitiator->RepositionTeam(CombatTargeting->EnemyTeam, TeamOrigin, SpawnOffset);
}

void AMonsterDatabase::SpawnMonsters(TArray<FString> MonsterNames)
{
	TArray<TSubclassOf<AMonster>*> Monsters;

	for (size_t i = 0; i < MonsterNames.Num(); i++)
	{
		TSubclassOf<AMonster>* Monster = DatabaseMap.Find(MonsterNames[i]);
		
		if(Monster != nullptr)
			Monsters.Add(Monster);
	}

	SpawnMonsters(Monsters);
}
