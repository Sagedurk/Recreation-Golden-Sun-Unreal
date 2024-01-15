// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTargeting.h"
#include <GoldenSun/CustomGameInstance.h>

#include "GoldenSun/Party.h"


// Sets default values
ACombatTargeting::ACombatTargeting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACombatTargeting::BeginPlay()
{
	Super::BeginPlay();

	
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetCombatTargeting(this);
		
		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &ACombatTargeting::GetGameInstanceReferences, 0.5f, false, 0.5f);
	
	}

	
}

// Called every frame
void ACombatTargeting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatTargeting::BeginTargeting(AUnit* Unit, ECombatTargetType TargetTeam) 
{
	CurrentUnit = Unit;
	CurrentUnit->MajorTargets.Empty();
	CurrentUnit->MinorTargets.Empty();

	switch (TargetTeam)
	{
	case ECombatTargetType::Ally:
		UnitTeam = GetAlliedTeam(Unit);
		SetTargetSelf(Unit);
		break;

	case ECombatTargetType::Enemy:
		UnitTeam = GetOpposingTeam(Unit);
		SetTargetEnemy(Unit);
		break;

	default:
		break;
	}
	
	CreateTargetMap();
	TrySetMinorTargets();
	SpawnTargetSelectors();


	//Change to correct input controls
	
}


void ACombatTargeting::FinishTargeting()
{
	AAdept* NextMember = Party->PeekNextMember();

	if(NextMember != nullptr)
	{
		ProceedToNextPartyMember();
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, TEXT("Initiate Combat Execution!"));

	ExecuteCombatTurn();
	
}

void ACombatTargeting::ProceedToNextPartyMember_Implementation()
{
	Reset();
	Party->TryGetNextMember();
}

void ACombatTargeting::ExecuteCombatTurn_Implementation()
{
	Reset();
	Party->ResetCurrentMember();
}

void ACombatTargeting::NextTarget()
{
	TArray<AUnit*> Team = *UnitTeam;

	int NewTargetIndex = GetTargetIndex() + 1;
	if (NewTargetIndex >= Team.Num())
		NewTargetIndex = 0;

	SetTargets(Team[NewTargetIndex]);
}

void ACombatTargeting::PreviousTarget()
{
	TArray<AUnit*> Team = *UnitTeam;

	int NewTargetIndex = GetTargetIndex() - 1;
	if (NewTargetIndex <= -1)
		NewTargetIndex = Team.Num() - 1;
	
	SetTargets(Team[NewTargetIndex]);
}

void ACombatTargeting::Return()
{
	Reset();
}

TArray<AUnit*>* ACombatTargeting::GetAlliedTeam(AUnit* Unit)
{
	if (AllyTeam.Contains(Unit))
		return &AllyTeam;
	
	if (EnemyTeam.Contains(Unit))
		return &EnemyTeam;

	return nullptr;
}

TArray<AUnit*>* ACombatTargeting::GetOpposingTeam(AUnit* Unit)
{
	if (AllyTeam.Contains(Unit))
		return &EnemyTeam;
	
	if (EnemyTeam.Contains(Unit))
		return &AllyTeam;

	return nullptr;
}

void ACombatTargeting::GetGameInstanceReferences()
{
	if(UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		Party = GameInstance->GetParty();
		
	}
	
}

int ACombatTargeting::GetTargetIndex() 
{
	int* TargetIndex = TargetMap.Find(CurrentUnit->CurrentTarget);
	return *TargetIndex;
}

void ACombatTargeting::CreateTargetMap()
{
	if(!TargetMap.IsEmpty())
		TargetMap.Empty();

	TArray<AUnit*> Team = *UnitTeam;

	for (size_t i = 0; i < Team.Num(); i++)
	{
		TargetMap.Add(Team[i], i);
	}
}

AUnit* ACombatTargeting::GetMiddleUnit(TArray<AUnit*> Units) 
{
	float MidPoint = (Units.Num() / 2.0f) + 0.5f;
	int UnitIndex = ((int)MidPoint) - 1;
	AUnit* Unit = Units[UnitIndex];

	return Unit;
}

void ACombatTargeting::Reset()
{
	UnitTeam = nullptr;
	CurrentUnit = nullptr;
	DestroyTargetSelectors();
}


void ACombatTargeting::SetTargets(AUnit* MainTarget)
{
	SetTarget(CurrentUnit, MainTarget);
	TrySetMinorTargets();
	SetTargetSelectors();
}

void ACombatTargeting::SetTarget(AUnit* Unit, AUnit* Target)
{
	Unit->CurrentTarget = Target;

	Unit->MajorTargets.Empty();
	Unit->MajorTargets.Add(Unit->CurrentTarget);
}

void ACombatTargeting::SetTargetEnemy(AUnit* Unit) 
{
	SetTarget(Unit, GetMiddleUnit(*UnitTeam));
}

void ACombatTargeting::SetTargetSelf(AUnit* Unit) 
{
	SetTarget(Unit, Unit);
}

void ACombatTargeting::TrySetMinorTargets()
{
	if (MinorTargetAmount < 2)
		return;

	TArray<AUnit*> Team = *UnitTeam;
	int TargetIndex = GetTargetIndex();

	CurrentUnit->MinorTargets.Empty();

	for (size_t i = 0; i < MinorTargetAmount / 2; i++)
	{
		int IndexDeviation = i + 1;
		int RightMinorIndex = TargetIndex + IndexDeviation;
		int LeftMinorIndex = TargetIndex - IndexDeviation;


		if (RightMinorIndex < Team.Num())
			CurrentUnit->MinorTargets.Add(Team[RightMinorIndex]);

		if (LeftMinorIndex >= 0)
			CurrentUnit->MinorTargets.Add(Team[LeftMinorIndex]);


	}
}

void ACombatTargeting::SpawnTargetSelectors() 
{
	SpawnMajorTargetSelectors();
	SpawnMinorTargetSelectors();
}

void ACombatTargeting::SpawnMajorTargetSelectors()
{
	if(!MajorSelectors.IsEmpty())
		DestroyMajorTargetSelectors();

	for (size_t i = 0; i < CurrentUnit->MajorTargets.Num(); i++)
	{
		AMajorTargetSelector* Selector = GetWorld()->SpawnActor<AMajorTargetSelector>(MajorSelectorBP);
		MajorSelectors.Add(Selector);

		SetMajorTargetSelector(Selector, CurrentUnit->MajorTargets[i]);
	}
}

void ACombatTargeting::SpawnMinorTargetSelectors()
{
	if (!MinorSelectors.IsEmpty())
		DestroyMinorTargetSelectors();

	for (size_t i = 0; i < CurrentUnit->MinorTargets.Num(); i++)
	{
		AMinorTargetSelector* Selector = GetWorld()->SpawnActor<AMinorTargetSelector>(MinorSelectorBP);
		MinorSelectors.Add(Selector);

		SetMinorTargetSelector(Selector, CurrentUnit->MinorTargets[i]);
	}
}


void ACombatTargeting::DestroyTargetSelectors() 
{
	DestroyMajorTargetSelectors();
	DestroyMinorTargetSelectors();
}


void ACombatTargeting::DestroyMajorTargetSelectors() 
{
	for (AMajorTargetSelector* MajorSelector : MajorSelectors)
	{
		MajorSelector->Destroy();
	}

	MajorSelectors.Empty();
}

void ACombatTargeting::DestroyMinorTargetSelectors() 
{
	for (AMinorTargetSelector* MinorSelector : MinorSelectors)
	{
		MinorSelector->Destroy();
	}

	MinorSelectors.Empty();
}

void ACombatTargeting::SetTargetSelectors() 
{
	SetMajorTargetSelectors();
	SetMinorTargetSelectors();
}

void ACombatTargeting::SetMajorTargetSelectors() 
{
	for (size_t i = 0; i < MajorSelectors.Num(); i++)
	{
		if (i < CurrentUnit->MajorTargets.Num())
			SetMajorTargetSelector(MajorSelectors[i], CurrentUnit->MajorTargets[i]);
		else
			HideMajorSelector(MajorSelectors[i]);
	}
}

void ACombatTargeting::SetMinorTargetSelectors()
{
	for (size_t i = 0; i < MinorSelectors.Num(); i++)
	{
		if (i < CurrentUnit->MinorTargets.Num())
			SetMinorTargetSelector(MinorSelectors[i], CurrentUnit->MinorTargets[i]);
		else
			HideMinorSelector(MinorSelectors[i]);
	}
}


void ACombatTargeting::SetMajorTargetSelector(AMajorTargetSelector* Selector, AUnit* Target) 
{
	FVector TargetLocation = Target->GetActorLocation() + (FVector3d::UpVector * 150);
	Selector->SetActorLocation(TargetLocation);

	Selector->SetActorHiddenInGame(false);
}

void ACombatTargeting::SetMinorTargetSelector(AMinorTargetSelector* Selector, AUnit* Target)
{
	FVector TargetLocation = Target->GetActorLocation() + (FVector3d::UpVector * 150);
	Selector->SetActorLocation(TargetLocation);
	
	Selector->SetActorHiddenInGame(false);
}


void ACombatTargeting::HideMajorSelector(AMajorTargetSelector* Selector)
{
	FVector TargetLocation = Selector->GetActorLocation() + (FVector3d::UpVector * 150);
	Selector->SetActorLocation(TargetLocation);

	Selector->SetActorHiddenInGame(true);
}

void ACombatTargeting::HideMinorSelector(AMinorTargetSelector* Selector)
{
	FVector TargetLocation = Selector->GetActorLocation() + (FVector3d::UpVector * 150);
	Selector->SetActorLocation(TargetLocation);

	Selector->SetActorHiddenInGame(true);
}




