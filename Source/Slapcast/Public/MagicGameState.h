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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridWidthPercentage;
	
protected:
	UPROPERTY()
	FVector2D StartPos;
	UPROPERTY()
	FVector2D MousePos;
	UPROPERTY()
	TArray<FIntVector2> Points;
	UPROPERTY()
	bool bIsDrawing = false;

};
