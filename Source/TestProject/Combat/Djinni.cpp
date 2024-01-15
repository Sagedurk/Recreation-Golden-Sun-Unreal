// Fill out your copyright notice in the Description page of Project Settings.


#include "Djinni.h"

// Sets default values
ADjinni::ADjinni()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADjinni::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADjinni::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADjinni::SetOwningAdept(AAdept* Adept)
{
	OwningAdept = Adept;
}