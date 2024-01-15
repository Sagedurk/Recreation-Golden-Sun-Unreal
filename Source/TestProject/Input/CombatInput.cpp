// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatInput.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

// Sets default values
ACombatInput::ACombatInput()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ACombatInput::BeginPlay()
{
	Super::BeginPlay();

	CustomGameInstance = Cast<UCustomGameInstance>(GetGameInstance());

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &ACombatInput::GetGameInstanceReferences, 0.5f, false, 0.5f);
	}

}

// Called every frame
void ACombatInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsInput == false)
	{
		FVector OldLocation = GetActorLocation();
		SetActorLocation(OldLocation + (FVector::RightVector * 1));
	}

}

// Called to bind functionality to input
void ACombatInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(NextTargetAction, ETriggerEvent::Triggered, this, &ACombatInput::CTWrapNextTarget);
		EnhancedInputComponent->BindAction(PreviousTargetAction, ETriggerEvent::Triggered, this, &ACombatInput::CTWrapPreviousTarget);
		EnhancedInputComponent->BindAction(FinishTargetingAction, ETriggerEvent::Triggered, this, &ACombatInput::CTWrapFinishTargeting);
		
	}

}

void ACombatInput::GetGameInstanceReferences()
{
	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
		CombatTargeting = GameInstance->GetCombatTargeting();
}

void ACombatInput::CTWrapNextTarget()
{
	if (CombatTargeting)
		CombatTargeting->NextTarget();
}

void ACombatInput::CTWrapPreviousTarget()
{	
	if (CombatTargeting)
		CombatTargeting->PreviousTarget();
}

void ACombatInput::CTWrapFinishTargeting()
{	
	if (CombatTargeting)
		CombatTargeting->FinishTargeting();
}