// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//#include <Engine/CanvasRenderTarget2D.h>

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

	virtual	void DrawHUD() override;

	float GetWidth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* LineMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DotMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineWidthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DotPercentage;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UMaterialInstanceDynamic* LineDynMaterial;
	UPROPERTY()
	UMaterialInstanceDynamic* DotDynMaterial;

private:
	void DrawDots(TArray<FVector2D>& Dots);
	void ComputeDotTriangles(TArray<FCanvasUVTri>& Triangles, FVector2D Point);
	void DrawLines(TArray<FVector2D>& Line);
	void ComputeLineTriangles(TArray<FCanvasUVTri>& Triangles, FVector2D Start, FVector2D End);
	void AddTriangles(TArray<FCanvasUVTri>& Triangles, FVector2D Points[], uint32 Length);

};

