// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicHUD.h"
#include <Kismet/KismetRenderingLibrary.h>
#include <Kismet/KismetMaterialLibrary.h>
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "MagicGameState.h"


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

	//LineDynMaterial = UMaterialInstanceDynamic::Create(LineMaterial, nullptr, TEXT("LineDynamicMaterial"));
	//LineDynMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), LineMaterial, TEXT("LineDynamicMaterial"));
	//FString a = LineDynMaterial->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("text: %s"), *a);
	//LineDynMaterial->SetFlags(RF_Transient);
	//RunDraw();
}

void AMagicHUD::BeginPlay()
{
	LineDynMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), LineMaterial, TEXT("LineDynamicMaterial"));
	FString a = LineDynMaterial->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("text: %s"), *a);
}

void AMagicHUD::Tick(float DeltaTime)
{
	//RenderTarget->UpdateResource();
	//this->PostRender();
	Super::Tick(DeltaTime);
}

void AMagicHUD::DrawHUD()
{
	//FVector2D view = GEngine->GameViewport();
	//UE_LOG(LogTemp, Warning, TEXT("text: %s"), view);
	//FVector2D Size = GetCanvasSize();
	//FVector2D Pos = Size / 2;
	TArray<FVector2D> Line = GetWorld()->GetGameState<AMagicGameState>()->GetLine();

	DrawLines(Line);
}

float AMagicHUD::GetWidth()
{
	FVector2D Size;
	GEngine->GameViewport->GetViewportSize(Size);
	return Size.X;
}

void AMagicHUD::DrawLines(TArray<FVector2D>& Line)
{
	TArray<FCanvasUVTri> Triangles;
	for (int32 j = 0; j < Line.Num() - 1; j++) {
		ComputeLineTriangles(Triangles, Line[j] * GetWidth(), Line[j + 1] * GetWidth());
	}


	Canvas->K2_DrawMaterialTriangle(LineDynMaterial, Triangles);
}

void AMagicHUD::ComputeLineTriangles(TArray<FCanvasUVTri>& Triangles, FVector2D Start, FVector2D End)
{
	FVector2D difference = End - Start;

	//UE_LOG(LogTemp, Warning, TEXT("triangles: %s %s"), *Start.ToString(), *End.ToString());

	FVector2D dir = difference.IsNearlyZero() ? FVector2D(1, 0) : difference.GetSafeNormal();

	FVector2D ortho_dir = FVector2D(-dir.Y, dir.X);

	float half_width = LineWidthPercentage * Canvas->SizeX;

	// make points 
	// [pos0, uv0, pos1, uv1,..]
	FVector2D points[16]{};
	for (int x = -1; x <= 1; x += 2) {
		FVector2D scaled_ortho = ortho_dir * half_width * x;

		// bottom extend
		points[x + 1 + 0] = Start - dir * half_width + scaled_ortho;
		points[x + 1 + 1] = FVector2D(x, -1);

		// bottom
		points[x + 1 + 4] = Start + scaled_ortho;
		points[x + 1 + 5] = FVector2D(x, 0);

		//top
		points[x + 1 + 8] = End + scaled_ortho;
		points[x + 1 + 9] = FVector2D(x, 0);

		//top extend
		points[x + 1 + 12] = End + dir * half_width + scaled_ortho;
		points[x + 1 + 13] = FVector2D(x, 1);
	}

	// add triangle (strip-wise)
	for (int32 j = 0; j < 6; j++) {
		FCanvasUVTri tri;
		tri.V0_Pos = points[j * 2 + 0];
		tri.V0_UV = points[j * 2 + 1];
		tri.V1_Pos = points[j * 2 + 2];
		tri.V1_UV = points[j * 2 + 3];
		tri.V2_Pos = points[j * 2 + 4];
		tri.V2_UV = points[j * 2 + 5];

		Triangles.Push(tri);
	}
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
