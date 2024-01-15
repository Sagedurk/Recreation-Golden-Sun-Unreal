// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element.generated.h"

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	Venus = 0		UMETA(DisplayName = "Venus"),
	Mars = 1		UMETA(DisplayName = "Mars"),
	Jupiter	= 2 	UMETA(DisplayName = "Jupiter"),
	Mercury	= 3 	UMETA(DisplayName = "Mercury"),
	None = 4		UMETA(DisplayName = "None"), 
};

USTRUCT()
struct FElement
{
	GENERATED_BODY()

	static EElementalType GetSymbioticElement(EElementalType Element);
	static EElementalType GetOppositeElement(EElementalType Element);
	static EElementalType GetUnrelatedElement(EElementalType Element);
	
};