// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Slate/WidgetRenderer.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"


#include "Kismet/BlueprintFunctionLibrary.h"
#include "VillagesLowLevelFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGESGOLDEDITION_API UVillagesLowLevelFunctionLibrary : public UBlueprintFunctionLibrary
{
	///GENERATED_BODY()
	GENERATED_UCLASS_BODY()

public:
		UFUNCTION(BlueprintCallable, Category = "VillagesLowLevel")
		static UTexture2D* TextureFromWidget(UUserWidget *const Widget, const FVector2D &DrawSize);
		///void TextureFromWidget(UUserWidget *const Widget, const FVector2D &DrawSize, UTexture2D* outTexture);

	
	
};
