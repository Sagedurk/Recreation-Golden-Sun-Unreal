// Fill out your copyright notice in the Description page of Project Settings.


#include "AdeptData.h"

FPrimaryAssetId UAdeptData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("Adept", GetFName());
}
