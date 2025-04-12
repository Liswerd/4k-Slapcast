// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Engine/CanvasRenderTarget2D.h>

#include "MagicHUD.generated.h"

/**
 *
 */
UCLASS()
class SLAPCAST_API AMagicHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMagicHUD();

	virtual void Tick(float DeltaTime) override;

	virtual	void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* LineMaterial;

private:

	//void RunDraw();


	UCanvasRenderTarget2D* RenderTarget;
	UMaterialInstanceDynamic* BaseDynMaterial;
	UMaterialInstanceDynamic* LineDynMaterial;

};
