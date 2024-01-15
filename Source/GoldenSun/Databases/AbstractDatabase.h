// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbstractDatabase.generated.h"

	template <typename T>
	concept ActorTemplate = requires(T Actor){ TIsTSubclassOf<T>::Value; };

UCLASS(Abstract)
class GOLDENSUN_API AAbstractDatabase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractDatabase();

	UPROPERTY(EditDefaultsOnly)
	FString NamingConventionPrefix;

	
	UPROPERTY(EditDefaultsOnly)
	bool bIsSingletonDatabase = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
	template<ActorTemplate T>
	TMap<FString, TSubclassOf<T>> ConvertDatabaseToMap(TArray<TSubclassOf<T>> Database);

	template<ActorTemplate T>
	T* SpawnActor(TSubclassOf<T> ActorToSpawn);

	template <ActorTemplate T>
	T* TryGetSpawnedDatabaseItem(TMap<FString,T*>* SpawnedItems,FString DatabaseItemName);

	template <ActorTemplate T>
	T* GetSpawnedDatabaseItem(TMap<FString,T*>* SpawnedItems, TMap<FString, TSubclassOf<T>>* DatabaseMap,FString DatabaseItemName);

	virtual void GetGameInstanceReferences() PURE_VIRTUAL();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	template<ActorTemplate T>
	T* GetDatabaseItem(FString ItemName, TMap<FString, T*>* SpawnedItems, TMap<FString, TSubclassOf<T>>* Database);
	
};

template <ActorTemplate T>
TMap<FString, TSubclassOf<T>> AAbstractDatabase::ConvertDatabaseToMap(TArray<TSubclassOf<T>> Database)
{
	TMap<FString, TSubclassOf<T>> Map;
	
	for (size_t i = 0; i < Database.Num(); i++)
	{
		TSubclassOf<T> DatabaseItem = Database[i];

		FString ItemName = DatabaseItem->GetName();

		if(NamingConventionPrefix != "")
		{
			if(!ItemName.Contains(NamingConventionPrefix))
				continue;
		
			ItemName.RemoveFromStart(NamingConventionPrefix);
		}
		
		ItemName.RemoveFromEnd("_C");

		if (!Map.Contains(ItemName))
		{
			Map.Add(ItemName, DatabaseItem);
		}
	}
	
	return Map;
}

template <ActorTemplate T>
T* AAbstractDatabase::SpawnActor(TSubclassOf<T> ActorToSpawn)
{
	return GetWorld()->SpawnActor<T>(ActorToSpawn);
}

template <ActorTemplate T>
T* AAbstractDatabase::TryGetSpawnedDatabaseItem(TMap<FString, T*>* SpawnedItems, FString DatabaseItemName)
{
	T** ActorPointer = SpawnedItems->Find(DatabaseItemName);
	
	if(ActorPointer != nullptr)
		return *ActorPointer;

	return nullptr;
}

template <ActorTemplate T>
T* AAbstractDatabase::GetSpawnedDatabaseItem(TMap<FString, T*>* SpawnedItems, TMap<FString, TSubclassOf<T>>* DatabaseMap, FString DatabaseItemName)
{
	T* Item = TryGetSpawnedDatabaseItem(SpawnedItems, DatabaseItemName);
	
	if(Item != nullptr)
		return Item;
	
	
	TSubclassOf<T> SubClass = *DatabaseMap->Find(DatabaseItemName);

	if(SubClass != nullptr)
	{
		T* Actor = SpawnActor(SubClass);
		SpawnedItems->Add(DatabaseItemName, Actor);
		
		return Actor;
	}


	const FString TemplateType = GetTypeName<T>();
	UE_LOG(LogTemp, Error, TEXT("%s not found in database of type %s!"), *DatabaseItemName, *TemplateType);
	return nullptr;
	
}

template <ActorTemplate T>
T* AAbstractDatabase::GetDatabaseItem(FString ItemName, TMap<FString, T*>* SpawnedItems,
	TMap<FString, TSubclassOf<T>>* Database)
{
	if(ItemName == "")
	{
		const FString TemplateType = GetTypeName<T>();
		UE_LOG(LogTemp, Error, TEXT("Empty name passed to database of type %s!"), *TemplateType);
		return nullptr;
	}

	
	return GetSpawnedDatabaseItem(SpawnedItems, Database, ItemName);
}