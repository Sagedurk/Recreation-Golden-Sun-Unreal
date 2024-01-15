// Fill out your copyright notice in the Description page of Project Settings.


#include "Element.h"

EElementalType FElement::GetSymbioticElement(EElementalType Element)
{
	switch (Element)
	{
	case EElementalType::Venus:
		return EElementalType::Mars;
		
	case EElementalType::Mars:
		return EElementalType::Venus;
		
	case EElementalType::Jupiter:
		return EElementalType::Mercury;
		
	case EElementalType::Mercury:
		return EElementalType::Jupiter;
		
	case EElementalType::None:
		return EElementalType::None;
		
	default: ;
		return EElementalType::None;
	}
}

EElementalType FElement::GetOppositeElement(EElementalType Element)
{
	switch (Element)
	{
	case EElementalType::Venus:
		return EElementalType::Jupiter;
		
	case EElementalType::Mars:
		return EElementalType::Mercury;
		
	case EElementalType::Jupiter:
		return EElementalType::Venus;
		
	case EElementalType::Mercury:
		return EElementalType::Mars;
		
	case EElementalType::None:
		return EElementalType::None;
		
	default: ;
		return EElementalType::None;
	}
}

EElementalType FElement::GetUnrelatedElement(EElementalType Element)
{
	switch (Element)
	{
	case EElementalType::Venus:
		return EElementalType::Mercury;
		
	case EElementalType::Mars:
		return EElementalType::Jupiter;
		
	case EElementalType::Jupiter:
		return EElementalType::Mars;
		
	case EElementalType::Mercury:
		return EElementalType::Venus;
		
	case EElementalType::None:
		return EElementalType::None;
		
	default: ;
		return EElementalType::None;
	}
}


