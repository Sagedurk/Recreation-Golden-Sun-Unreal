// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Adept.h"
#include "Databases/AdeptDatabase.h"
#include "GameFramework/Actor.h"
#include "Party.generated.h"


UCLASS()
class GOLDENSUN_API AParty : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParty();

	UPROPERTY(BlueprintReadWrite)
	TArray<AAdept*> PartyMembers;

	UPROPERTY()
	AAdeptDatabase* AdeptDatabase;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> DebugPartyNames;
	
private:

	UFUNCTION(BlueprintCallable)
	void TryMoveMember(AAdept* PartyMember, int NewIndex);

	UPROPERTY()
	AAdept* CurrentPartyMember;

protected:
	void GetGameInstanceReferences();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void AddMember(FString AdeptName);

	void RemoveMember(AAdept* PartyMember);


	UFUNCTION(BlueprintCallable)
	void TryMoveMemberForward(AAdept* PartyMember);

	UFUNCTION(BlueprintCallable)
	void TryMoveMemberBack(AAdept* PartyMember);

	UFUNCTION(BlueprintCallable)
	AAdept* GetCurrentMember();
	
	void SetCurrentMember(AAdept* Member);
	
	UFUNCTION(BlueprintCallable)
	AAdept* TryGetNextMember();
	
	AAdept* PeekNextMember();

	UFUNCTION(BlueprintCallable)
	AAdept* TryGetPreviousMember();
	
	AAdept* PeekPreviousMember();

	void ResetCurrentMember();
};
