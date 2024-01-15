// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractDatabase.h"

// Sets default values
AAbstractDatabase::AAbstractDatabase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbstractDatabase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbstractDatabase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

