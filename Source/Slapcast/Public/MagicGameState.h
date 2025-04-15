// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MagicGameState.generated.h"

//class Drawing {
//
//};

/**
 * 
 */
UCLASS()
class SLAPCAST_API AMagicGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	void StartDraw();
	void TickPoint(FVector2D pos);
	void EndDraw();

	TArray<FVector2D> GetLine();
	TArray<FVector2D> GetDots();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridWidthPercentage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DotWidthPercentage;

protected:
	UPROPERTY()
	FVector2D StartPos;
	UPROPERTY()
	FVector2D EndPos;
	UPROPERTY()
	FVector2D MousePos;
	//UPROPERTY()
	//TArray<FVector2D> LineArray;
	//UPROPERTY()
	//TArray<FVector2D> DotArray;
	UPROPERTY()
	TArray<FIntVector2> ShapePoints;
	UPROPERTY()
	TSet<FIntVector2> ShownDots;
	UPROPERTY()
	bool bIsDrawing = false;


private:
	void TickDotCollision();
	FIntVector2 CheckDotsAroundCollsion(FIntVector2 LineStart);
	bool CheckDotLineCollsion(FIntVector2 LineStart, FIntVector2 DotPos);
	void AddDotSquare(FIntVector2 Pos);
	//static bool CheckCircleLineCollsion(FVector2D start, FVector2D end, FVector2D DotPos, );
};
