// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicComponent.h"

// Fill out your copyright notice in the Description page of Project Settings.


//#include "MagicGameState.h"

void UMagicComponent::StartDraw(FVector SendPos)
{
	bIsDrawing = true;

	// clear all arrays
	//LineArray.Empty();
	//DotArray.Empty();
	// TODO fix
	Shapes.Empty();


	if (Shapes.Num() > 0) {
		Shapes.Last().Points.Shrink();
	}
	Shapes.PushLast(FShape(MousePos, SendPos, FIntVector2::ZeroValue));
	//ShownDots.Empty();


	/*	StartPos = MousePos*/;
	AddDotSquare(FIntVector2::ZeroValue);

}
void UMagicComponent::TickPoint(FVector2D NewMousePos)
{
	MousePos = NewMousePos;
	if (bIsDrawing) {
		TickDotCollision();
	}
}

void UMagicComponent::EndDraw()
{
	bIsDrawing = false;
	//if (ShapePoints.IsEmpty()) {
	ShownDots.Empty();
	//}
}

UMagicComponent::FDotIterator UMagicComponent::GetDotIterator()
{
	return ShownDots.CreateConstIterator();
}

UMagicComponent::FShapeArray& UMagicComponent::GetShapeArray()
{
	return Shapes;
}

//bool UMagicComponent::GetDot(FDotIterator& Iterator, FVector2D& Position)
//{
//	bool ret = (bool)Iterator;
//	if (ret) {
//		//SAFTEY: Will always have current shape as: to have an iterator of dots, we must be drawing 
//		FShape& CurrShape = Shapes.Last();
//		Position = FVector2D(Iterator.Key().X, Iterator.Key().Y) * GridWidthPercentage + CurrShape.StartPos;
//		++Iterator;
//	}
//	return ret;
//}

//bool UMagicComponent::GetShape(FShape*& Shape, int32 Index)
//{
//	bool ret = Index < Shapes.Num();
//	if (ret) {
//		Shape = &Shapes[Index];
//	}
//	return ret;
//}

FVector2D UMagicComponent::GetDotPosition(FDotIterator& Iterator)
{
	FIntVector2 Point = Iterator.Key();
	//SAFTEY: Will always have current shape as: to have an iterator of dots, we must be drawing 
	FShape& Shape = Shapes.Last();
	return FVector2D(Point.X, Point.Y) * GridWidthPercentage + Shape.StartPos;
}


FVector2D UMagicComponent::GetPosition(FIntVector2 Point, FShape& Shape) const
{
	return  FVector2D(Point.X, Point.Y) * GridWidthPercentage + Shape.StartPos;
}

bool UMagicComponent::GetMousePosition(FVector2D& Position)
{
	Position = MousePos;
	return bIsDrawing;
}

//bool UMagicComponent::GetPoint(FVector2D& Position, FShape*& Shape, int32 Index)
//{
//	bool ret = Index < Shape->Points.Num();
//	if (ret) {
//		Position = FVector2D(Shape->Points[Index].X, Shape->Points[Index].Y) * GridWidthPercentage + Shape->StartPos;
//	}
//	else if (bIsDrawing && Shape == &Shapes[Shapes.Num() - 1] && Index == Shape->Points.Num()) {
//		Position = MousePos;
//		ret = true;
//	}
//
//	return ret;
//}


//TArray<FVector2D> UMagicComponent::GetLine()
//{
//	TArray<FVector2D> Line;
//
//	Line.Push(StartPos);
//	for (int j = 0; j < Shapes.Num(); j++) {
//		Line.Push(FVector2D(Shapes[j].X, Shapes[j].Y) * GridWidthPercentage + StartPos);
//	}
//	if (bIsDrawing)
//		Line.Push(MousePos);
//	return Line;
//}
//
//TArray<FVector2D> UMagicComponent::GetDots()
//{
//	TArray<FVector2D> Dots;
//
//	TMap<FIntVector2, uint64>::TConstIterator Iter = ShownDots.CreateConstIterator();
//	for (; Iter; ++Iter) {
//		Dots.Push(FVector2D(Iter.Key().X, Iter.Key().Y) * GridWidthPercentage + StartPos);
//	}
//	return Dots;
//}


//FIntVector2 GetLastOrDefault(TArray<FIntVector2>& Points, int32 IndexFromTheEnd = 0) {
//	FIntVector2 LineStart(0, 0);
//	if (Points.Num() > IndexFromTheEnd) {
//		LineStart = Points.Last(IndexFromTheEnd);
//	}
//	return LineStart;
//}

void UMagicComponent::TickDotCollision()
{
	TArray<FIntVector2>& Points = Shapes.Last().Points;
	FIntVector2 LineStart = Points.Last();
	//ShapePoints.FindLast(LineStart);
	FIntVector2 DotCollison = CheckDotsAroundCollsion(LineStart);
	// not zero - changed point
	if (!DotCollison.IsZero()) {
		FIntVector2 NewPoint = LineStart + DotCollison;
		bool should_add_point = true;
		// check whether went back
		if (Points.Num() >= 2) {
			//FIntVector2 LastLineStart = GetLastOrDefault(Points, 1);
			// if has index -1
			// else leave as default 0,0
			//if (Shapes.Num() >= 2) {
			FIntVector2 LastLineStart = Points.Last(1);
			//}
			if (LastLineStart == NewPoint) {
				RemoveDotSquare(LineStart);
				Points.Pop();
				should_add_point = false;
			}

		}
		if (should_add_point) {
			Points.Push(NewPoint);
			AddDotSquare(NewPoint);
			TickShapeRecognizer();
		}
	}
}

FIntVector2 UMagicComponent::CheckDotsAroundCollsion(FIntVector2 LineStart)
{
	//SAFTEY: Will always have current shape as: to have an iterator of dots, we must be drawing 
	FShape& CurrShape = Shapes.Last();
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			if (y != 0 || x != 0) {
				if (CheckDotLineCollsion(LineStart, FIntVector2(x, y) + LineStart, CurrShape.StartPos)) {
					return FIntVector2(x, y);
				}
			}
		}
	}
	return FIntVector2::ZeroValue;
}

bool UMagicComponent::CheckDotLineCollsion(FIntVector2 LineStart, FIntVector2 DotPos, FVector2D StartPos)
{
	/*
		https://stackoverflow.com/a/1084899/9406364
		E is the starting point of the ray,
		L is the end point of the ray,
		C is the center of sphere you're testing against
		r is the radius of that sphere
		d = L - E ( Direction vector of ray, from start to end )
		f = E - C ( Vector from center sphere to ray start )
	*/


	FVector2D L = MousePos;
	FVector2D E = FVector2D(LineStart.X, LineStart.Y) * GridWidthPercentage + StartPos;
	FVector2D C = FVector2D(DotPos.X, DotPos.Y) * GridWidthPercentage + StartPos;
	float r = DotWidthPercentage;

	FVector2D d = L - E;
	FVector2D f = E - C;
	float a = d.Dot(d);
	float b = 2 * f.Dot(d);
	float c = f.Dot(f) - r * r;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return false;
	}
	else
	{
		// ray didn't totally miss sphere,
		// so there is a solution to
		// the equation.

		discriminant = sqrt(discriminant);

		// either solution may be on or off the ray so need to test both
		// t1 is always the smaller value, because BOTH discriminant and
		// a are nonnegative.
		float t1 = (-b - discriminant) / (2 * a);
		float t2 = (-b + discriminant) / (2 * a);

		// 3x HIT cases:
		//          -o->             --|-->  |            |  --|->
		// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		// 3x MISS cases:
		//       ->  o                     o ->              | -> |
		// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		if (t1 >= 0 && t1 <= 1)
		{
			// t1 is the intersection, and it's closer than t2
			// (since t1 uses -b - discriminant)
			// Impale, Poke
			return true;
		}

		// here t1 didn't intersect so we are either started
		// inside the sphere or completely past it
		if (t2 >= 0 && t2 <= 1)
		{
			// ExitWound
			return true;
		}

		// no intn: FallShort, Past, CompletelyInside
		return false;
	}
}

void UMagicComponent::TickShapeRecognizer()
{
	FShape& Shape = Shapes.Last();
	TArray<FIntVector2>& Points = Shape.Points;
	for (int32 j = 0; j < Spells.Num(); j++) {
		UMagicSkill& Spell = *Spells[j];
		if (IsShapeEqual(Points, Spell)) {
			FIntVector2 LastPoint = Points.Last();
			int32 ShapePointCount = Spell.Shape.Num() + 1;
			// Spell is not exactly complete -- need extra shape to hold extra points
			if (Points.Num() != ShapePointCount) {
				TArray<FIntVector2> NewPoints;
				NewPoints.Append(Points.GetData() + Points.Num() - ShapePointCount, ShapePointCount);
				//NewPoints.Shrink();
				Shapes.PushLast(FShape(Shape.StartPos, Shape.SendPos, NewPoints));

				Points.SetNum(Points.Num() - ShapePointCount + 1, false);
				Points.Shrink();
			}

			FShape& NewShape = Shapes.Last();
			NewShape.bSuccess = true;
			NewShape.Points.Shrink();

			// run the spell
			FVector Start = GetOwner()->GetActorLocation() + FVector::UpVector * 45;
			UE_LOG(LogTemp, Warning, TEXT("Cast Vector: %s %s"), *Start.ToString(), *Shape.SendPos.ToString());
			Spell.ExecCast(Start, Shape.SendPos);

			Shapes.PushLast(FShape(Shape.StartPos, Shape.SendPos, LastPoint));
		}
	}
}

bool UMagicComponent::IsShapeEqual(TArray<FIntVector2>& CurrShape, UMagicSkill& Spell)
{
	// current shape not long enough
	int32 IndexOffset = CurrShape.Num() - Spell.Shape.Num() - 1;
	if (IndexOffset < 0) {
		return false;
	}

	FIntVector2 PointOffset = CurrShape[IndexOffset];
	for (int32 j = 0; j < Spell.Shape.Num(); j++) {
		auto Curr = CurrShape[j + IndexOffset + 1] - PointOffset;
		auto Needed = Spell.Shape[j];
		//UE_LOG(LogTemp, Warning, TEXT("Shape: %s %s"), *Curr.ToString(), *Needed.ToString());

		if (Curr.X != Needed.X || Curr.Y != -Needed.Y) {
			return false;
		}
	}
	return true;

}

void UMagicComponent::AddDotSquare(FIntVector2 Pos)
{
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			ShownDots.FindOrAdd(Pos + FIntVector2(x, y))++;
		}
	}
}

void UMagicComponent::RemoveDotSquare(FIntVector2 Pos)
{
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			FIntVector2 Key = Pos + FIntVector2(x, y);
			uint64* Val = ShownDots.Find(Key);
			if (Val && -- (*Val) == 0) {
				ShownDots.FindAndRemoveChecked(Key);
			}
		}
	}
}
