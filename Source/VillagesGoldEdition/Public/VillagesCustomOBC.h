// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "VillagesCustomOBC.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class VILLAGESGOLDEDITION_API AVillagesCustomOBC : public AOnlineBeaconClient
{
	GENERATED_BODY()

public:

	AVillagesCustomOBC(const FObjectInitializer & ObjectInitializer);

	//return whether Attemped to connect or not
	UFUNCTION(BlueprintCallable, Category = "Villages")
		bool tryToConnectURL(FString URL, int32 port = 7787);

		UFUNCTION(BlueprintCallable, Category = "Villages")
			FString GetBeaconType();
		UFUNCTION(BlueprintCallable, Category = "Villages")
			void DestroyBeacon() override;
		UFUNCTION(BlueprintImplementableEvent, Category = "Villages")
			void OnConnected() override;
		
	
};
