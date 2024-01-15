// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseInterface.h"

#include "Kismet/GameplayStatics.h"

// Add default functionality here for any IDatabaseInterface functions that are not pure virtual.
void IDatabaseInterface::ConvertDatabaseToMap(TArray<TSubclassOf<AActor>> Database,
	TMap<FString, TSubclassOf<AActor>> Map, FString NamePrefix)
{
	if (!Map.IsEmpty())
		Map.Empty();

	for (size_t i = 0; i < Database.Num(); i++)
	{
		TSubclassOf<AActor> DatabaseItem = Database[i];
		
		FString ItemName = DatabaseItem->GetName();
		ItemName.RemoveFromStart(NamePrefix);
		ItemName.RemoveFromEnd("_C");

		if (!Map.Contains(ItemName))
		{
			Map.Add(ItemName, DatabaseItem);
		}
	}

}

TSubclassOf<AActor>* IDatabaseInterface::TrySpawnItem(UWorld* World, TSubclassOf<AActor> ActorToSpawn)
{
	//if(World == nullptr)
		return nullptr;

	
	//return World->SpawnActor<TSubclassOf<AActor>>(ActorToSpawn);
}

TArray<TSubclassOf<AActor>*> IDatabaseInterface::TrySpawnItems(UWorld* World, TArray<TSubclassOf<AActor>> ActorsToSpawn)
{
	TArray<TSubclassOf<AActor>*> ActorArray;

	for (size_t i = 0; i < ActorsToSpawn.Num(); i++)
	{
		TSubclassOf<AActor>* SpawnedActor = TrySpawnItem(World, ActorsToSpawn[i]);

		if(SpawnedActor != nullptr)
		ActorArray.Add(SpawnedActor);
	}

	return ActorArray;
	
}
