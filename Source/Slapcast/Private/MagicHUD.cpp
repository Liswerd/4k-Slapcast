// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicHUD.h"
#include <Kismet/KismetRenderingLibrary.h>
#include <Kismet/KismetMaterialLibrary.h>
#include "Engine/Canvas.h"


AMagicHUD::AMagicHUD()
{
	//// make render target
	//RenderTarget = NewObject<UCanvasRenderTarget2D>(this, TEXT("RenderTarget"));
	//RenderTarget->ResizeTarget(GSystemResolution.ResX, GSystemResolution.ResY);

	//// clear render target
	//RenderTarget->ClearColor = FColor(0);
	//UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), RenderTarget, RenderTarget->ClearColor);

	// make base dynamic material
	//BaseDynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this, TEXT("BaseDynamicMaterial"));
	//BaseDynMaterial->SetTextureParameterValue("render_target", RenderTarget);

	LineDynMaterial = UMaterialInstanceDynamic::Create(LineMaterial, nullptr, TEXT("LineDynamicMaterial"));
	//UKismetMaterialLibrary
	//LineDynMaterial->set
	//RunDraw();
}

void AMagicHUD::Tick(float DeltaTime)
{
	//RenderTarget->UpdateResource();
	//this->PostRender();
}

void AMagicHUD::DrawHUD()
{
	FVector2D Size = FVector2D(Canvas->SizeX, Canvas->SizeY);
	FVector2D Pos = Size / 2;
	//LineDynMaterial->time
	Canvas->K2_DrawMaterial(LineMaterial, Pos, FVector2D(50, 50), FVector2D(0, 0));
}

//void AMagicHUD::RunDraw()
//{
//	UCanvas* pCanvas;
//	FVector2D Size;
//	FDrawToRenderTargetContext Context;
//
//	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(GetWorld(), RenderTarget, pCanvas, Size, Context);
//
//	this->Canvas;
//
//	//UKismetRenderingLibrary::mater
//
//	FVector2D Pos = Size / 2;
//
//	pCanvas->K2_DrawMaterial(LineDynMaterial, Pos, FVector2D(50,50), FVector2D(0, 0));
//
//
//	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), Context);
//}



/*ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> MinimapTexObj(TEXT("TextureRenderTarget2D'/Game/Textures/MinimapTexture.MinimapTexture'"));
texture = MinimapTexObj.Object;*/
////textuer
//texture->TextureTarget = re
//class USceneCaptureComponent2D* sceneCaptureActor = 
//	(class USceneCaptureComponent2D*)GetWorld()->SpawnActor<USceneCaptureComponent2D>(USceneCaptureComponent2D::StaticClass());nderTarget2D;
