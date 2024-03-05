// Fill out your copyright notice in the Description page of Project Settings.


#include "Party.h"
#include "CustomGameInstance.h"

// Sets default values
AParty::AParty()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParty::BeginPlay()
{
	Super::BeginPlay();

	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		GameInstance->TrySetParty(this);
		
		FTimerHandle TimerHandle; 
		GameInstance->TimerManager->SetTimer(TimerHandle, this, &AParty::GetGameInstanceReferences, 0.5f, false, 0.5f);

	}
	
}

// Called every frame
void AParty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParty::AddMember(FString AdeptName)
{
	AAdept* Adept = AdeptDatabase->SpawnAdept(AdeptName);
	PartyMembers.Add(Adept);
}

void AParty::RemoveMember(AAdept* PartyMember)
{
	PartyMembers.Remove(PartyMember);
}

void AParty::TryMoveMember(AAdept* PartyMember, int NewIndex)
{
	if (!PartyMembers.IsValidIndex(NewIndex))
		return;
	
	int OldIndex = PartyMembers.Find(PartyMember);

	PartyMembers.Swap(OldIndex, NewIndex);
	
}

void AParty::GetGameInstanceReferences()
{
	if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		AdeptDatabase = GameInstance->GetAdeptDatabase();


		for (FString DebugPartyName : DebugPartyNames)
		{
			AddMember(DebugPartyName);
		}
	
	}
}

void AParty::TryMoveMemberForward(AAdept* PartyMember)
{
	int MemberIndex = PartyMembers.Find(PartyMember);
	TryMoveMember(PartyMember, MemberIndex + 1);
}

void AParty::TryMoveMemberBack(AAdept* PartyMember)
{
	int MemberIndex = PartyMembers.Find(PartyMember);
	TryMoveMember(PartyMember, MemberIndex - 1);
}

AAdept* AParty::GetCurrentMember()
{
	if(CurrentPartyMember == nullptr)
		SetCurrentMember(PartyMembers[0]);
		
	return CurrentPartyMember;
}

void AParty::SetCurrentMember(AAdept* Member)
{
	CurrentPartyMember = Member;
}

AAdept* AParty::TryGetNextMember()
{
	AAdept* NextMember = PeekNextMember();

	if(NextMember == nullptr)
		return nullptr;
	
	SetCurrentMember(NextMember);
	
	return NextMember;
	
}

AAdept* AParty::PeekNextMember()
{
	AAdept* CurrentMember = GetCurrentMember();
	
	int NextMemberIndex = PartyMembers.Find(CurrentMember) + 1;

	if(NextMemberIndex >= PartyMembers.Num())
		return nullptr;
	
	AAdept* NextMember = PartyMembers[NextMemberIndex];
	
	return NextMember;
}

AAdept* AParty::TryGetPreviousMember()
{
	AAdept* PreviousMember = PeekPreviousMember();

	if(PreviousMember == nullptr)
		return nullptr;
	
	SetCurrentMember(PreviousMember);
	
	return PreviousMember;
}

AAdept* AParty::PeekPreviousMember()
{
	AAdept* CurrentMember = GetCurrentMember();
	
	int PreviousMemberIndex = PartyMembers.Find(CurrentMember) - 1;

	if(PreviousMemberIndex < 0)
		return nullptr;
	
	AAdept* PreviousMember = PartyMembers[PreviousMemberIndex];
	
	return PreviousMember;
	
}

void AParty::ResetCurrentMember()
{
	SetCurrentMember(PartyMembers[0]);
}

int32 AParty::GetPartyDjinnAmountByElement(EElementalType DjinnElement)
{
	int32 PartyDjinnAmount = 0;
	for (AAdept* PartyMember : PartyMembers)
	{
		int32 AdeptDjinnAmount = PartyMember->GetDjinnAmount(DjinnElement);
		PartyDjinnAmount += AdeptDjinnAmount;
	}

	return PartyDjinnAmount;
}

int32 AParty::GetPartyDjinnAmountByState(EDjinniState State)
{
	int32 PartyDjinnAmount = 0;
	for (AAdept* PartyMember : PartyMembers)
	{
		int32 AdeptDjinnAmount = PartyMember->GetDjinnAmount(State);
		PartyDjinnAmount += AdeptDjinnAmount;
	}

	return PartyDjinnAmount;
}

int32 AParty::GetPartyDjinnAmount(EElementalType DjinnElement, EDjinniState State)
{
	int32 PartyDjinnAmount = 0;
	for (AAdept* PartyMember : PartyMembers)
	{
		int32 AdeptDjinnAmount = PartyMember->GetDjinnAmount(DjinnElement, State);
		PartyDjinnAmount += AdeptDjinnAmount;
	}

	return PartyDjinnAmount;
}
