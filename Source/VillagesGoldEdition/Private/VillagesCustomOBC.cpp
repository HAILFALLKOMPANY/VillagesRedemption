// Fill out your copyright notice in the Description page of Project Settings.

#include "VillagesCustomOBC.h"

AVillagesCustomOBC::AVillagesCustomOBC(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	///
}

FString AVillagesCustomOBC::GetBeaconType()
{
	return Super::GetBeaconType();
}

void AVillagesCustomOBC::DestroyBeacon()
{
	Super::DestroyBeacon();
}

bool AVillagesCustomOBC::tryToConnectURL(FString URL, int32 port)
{
	FURL tempURL(NULL, *URL, TRAVEL_Absolute);
	if (port != 0)
	{
		tempURL.Port = port;
	}
	return InitClient(tempURL);
}
