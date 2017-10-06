// Fill out your copyright notice in the Description page of Project Settings.

#include "VillagesCustomOBH.h"


AVillagesCustomOBH::AVillagesCustomOBH(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	//set default listen port
	configListenPort = 7787;
	setListenPort(configListenPort);
	turnOnBeaconHost();
}

void AVillagesCustomOBH::setListenPort(int32 port)
{
	ListenPort = port;
}

void AVillagesCustomOBH::RegisterHost(AOnlineBeaconHostObject * NewHostObject)
{
	Super::RegisterHost(NewHostObject);
}

void AVillagesCustomOBH::UnregisterHost(const FString & BeaconType)
{
	Super::UnregisterHost(BeaconType);
}

bool AVillagesCustomOBH::InitHost()
{
	setListenPort(configListenPort);
	return Super::InitHost();
}

int32 AVillagesCustomOBH::GetListenPort()
{
	return Super::GetListenPort();
}

void AVillagesCustomOBH::turnOnBeaconHost()
{
	BeaconState = EBeaconState::AllowRequests;
}

void AVillagesCustomOBH::turnOffBeaconHost()
{
	BeaconState = EBeaconState::DenyRequests;
}

