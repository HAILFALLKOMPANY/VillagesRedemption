// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHost.h"
#include "VillagesCustomOBH.generated.h"

/**
 * 
 */


UCLASS(Blueprintable, BlueprintType)
class VILLAGESGOLDEDITION_API AVillagesCustomOBH : public AOnlineBeaconHost
{
	GENERATED_BODY()
	
public:
	AVillagesCustomOBH(const FObjectInitializer & ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void setListenPort(int32 port);
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void turnOnBeaconHost();
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void turnOffBeaconHost();

	UFUNCTION(BlueprintCallable, Category = "Villages")
		void RegisterHost(AOnlineBeaconHostObject * NewHostObject) override;
	UFUNCTION(BlueprintCallable, Category = "Villages")
		void UnregisterHost(const FString & BeaconType) override;
	UFUNCTION(BlueprintCallable, Category = "Villages")
		bool InitHost() override;
	UFUNCTION(BlueprintCallable, Category = "Villages")
		int32 GetListenPort() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Villages")
		int32 configListenPort;
};
