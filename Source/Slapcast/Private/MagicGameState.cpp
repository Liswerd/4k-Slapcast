// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicGameState.h"

void AMagicGameState::StartDraw()
{
	bIsDrawing = true;
	StartPos = MousePos;
	Points.Empty();
	Points.Push(FIntVector2::ZeroValue);
}
void AMagicGameState::TickPoint(FVector2D NewMousePos)
{
	MousePos = NewMousePos;
}

void AMagicGameState::EndDraw()
{
	bIsDrawing = false;
}

TArray<FVector2D> AMagicGameState::GetLine()
{
	TArray<FVector2D> Line;
	for (int j = 0; j < Points.Num(); j++) {
		Line.Push(FVector2D(Points[j].X, Points[j].Y) * GridWidthPercentage + StartPos);
	}
	Line.Push(MousePos);
	return Line;
}

