// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GoldenSun/Combat/CombatTargeting.h>
#include <InputMappingContext.h>
#include <GoldenSun/CustomGameInstance.h>
#include "CombatInput.generated.h"

class UInputAction;

UCLASS()
class GOLDENSUN_API ACombatInput : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatInput();
	void GetGameInstanceReferences();

	/** Combat Target Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextTargetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PreviousTargetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FinishTargetingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchTeamAction;



	bool bIsInput = true;

	ACombatTargeting* CombatTargeting;
	UCustomGameInstance* CustomGameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CTWrapNextTarget();

	void CTWrapPreviousTarget();
	void CTWrapFinishTargeting();
};
