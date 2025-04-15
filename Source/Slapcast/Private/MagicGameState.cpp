// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicGameState.h"

void AMagicGameState::StartDraw()
{
	bIsDrawing = true;

	// clear all arrays
	//LineArray.Empty();
	//DotArray.Empty();
	ShapePoints.Empty();
	ShownDots.Empty();


	StartPos = MousePos;
	ShapePoints.Push(FIntVector2::ZeroValue);
	AddDotSquare(FIntVector2::ZeroValue);

	ShapePoints.Push(FIntVector2(1,1));
	AddDotSquare(FIntVector2(1,1));

	ShapePoints.Push(FIntVector2(1, 0));
	AddDotSquare(FIntVector2(1, 0));

	ShapePoints.Push(FIntVector2(1, -1));
	AddDotSquare(FIntVector2(1, -1));

}
void AMagicGameState::TickPoint(FVector2D NewMousePos)
{
	MousePos = NewMousePos;
}

void AMagicGameState::EndDraw()
{
	bIsDrawing = false;
}

void AMagicGameState::AddDotSquare(FIntVector2 pos)
{
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			//if (y != x) {
				ShownDots.Add(pos + FIntVector2(x, y));
			//}
		}
	}
}

TArray<FVector2D> AMagicGameState::GetLine()
{
	TArray<FVector2D> Line;
	for (int j = 0; j < ShapePoints.Num(); j++) {
		Line.Push(FVector2D(ShapePoints[j].X, ShapePoints[j].Y) * GridWidthPercentage + StartPos);
	}
	Line.Push(MousePos);
	return Line;
}

TArray<FVector2D> AMagicGameState::GetDots()
{
	TArray<FVector2D> Dots;

	TSet<FIntVector2>::TConstIterator Iter = ShownDots.CreateConstIterator();
	for (; Iter; ++Iter) {
		Dots.Push(FVector2D(Iter->X, Iter->Y) * GridWidthPercentage + StartPos);
	}
	return Dots;
}

