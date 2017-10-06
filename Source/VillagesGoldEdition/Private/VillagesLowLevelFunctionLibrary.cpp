// Fill out your copyright notice in the Description page of Project Settings.

#include "VillagesLowLevelFunctionLibrary.h"

UVillagesLowLevelFunctionLibrary::UVillagesLowLevelFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UTexture2D* UVillagesLowLevelFunctionLibrary::TextureFromWidget(UUserWidget *const Widget, const FVector2D &DrawSize)

///void UVillagesLowLevelFunctionLibrary::TextureFromWidget(UUserWidget *const Widget, const FVector2D &DrawSize, UTexture2D* outTexture)
{
	if (FSlateApplication::IsInitialized()
		&& Widget != NULL && Widget->IsValidLowLevel()
		&& DrawSize.X >= 1 && DrawSize.Y >= 1)
	{
		TSharedPtr<SWidget> SlateWidget(Widget->TakeWidget());
		if (!SlateWidget.IsValid()) 
			return NULL;
			///outTexture = NULL;
		TSharedPtr<FWidgetRenderer> WidgetRenderer = MakeShareable(new FWidgetRenderer(true));
		if (!WidgetRenderer.IsValid()) 
			return NULL;
			///outTexture = NULL;

		UTextureRenderTarget2D *TextureRenderTarget = WidgetRenderer->DrawWidget(SlateWidget.ToSharedRef(), DrawSize);
		// Creates Texture2D to store RenderTexture content
		UTexture2D *Texture = UTexture2D::CreateTransient(DrawSize.X, DrawSize.Y, PF_B8G8R8A8);
#if WITH_EDITORONLY_DATA
		Texture->MipGenSettings = TMGS_NoMipmaps;
#endif

		// Lock and copies the data between the textures
		TArray<FColor> SurfData;
		FRenderTarget *RenderTarget = TextureRenderTarget->GameThread_GetRenderTargetResource();
		RenderTarget->ReadPixels(SurfData);

		void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		const int32 TextureDataSize = SurfData.Num() * 4;
		FMemory::Memcpy(TextureData, SurfData.GetData(), TextureDataSize);
		Texture->PlatformData->Mips[0].BulkData.Unlock();
		Texture->UpdateResource();

		// Free resources
		SurfData.Empty();
		TextureRenderTarget->ConditionalBeginDestroy();
		SlateWidget.Reset();
		WidgetRenderer.Reset();

		return Texture;
		///outTexture = Texture;
	}
	return NULL;
	///outTexture = NULL;
}

