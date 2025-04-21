// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Containers/Deque.h"
#include "MagicSkill.h"

#include "MagicComponent.generated.h"


USTRUCT(BlueprintType)
struct FShape {
	GENERATED_BODY()

	FShape() {

	}

	FShape(FVector2D StartPosition, FVector SendPosition, FIntVector2 StartPoint) {
		SendPos = SendPosition;
		StartPos = StartPosition;
		Points.Push(StartPoint);
	}

	FShape(FVector2D StartPosition, FVector SendPosition, TArray<FIntVector2> StartPoint) {
		SendPos = SendPosition;
		StartPos = StartPosition;
		Points = StartPoint;
	}

	UPROPERTY()
	TArray<FIntVector2> Points;

	UPROPERTY()
	FVector SendPos;

	UPROPERTY()
	FVector2D StartPos;

	UPROPERTY()
	bool bSuccess = false;
};

UCLASS()
class SLAPCAST_API UMagicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
public:
	using FDotIterator = TMap<FIntVector2, uint64>::TConstIterator;
	using FShapeArray = TDeque<FShape>;

public:
	void StartDraw(FVector SendPos);
	void TickPoint(FVector2D pos);
	void EndDraw();

	//TArray<FVector2D> GetLine();
	//TArray<FVector2D> GetDots();
	FDotIterator GetDotIterator();
	FShapeArray& GetShapeArray();

	//bool GetDot(FDotIterator& Iterator, FVector2D& Position);


	FVector2D GetDotPosition(FDotIterator& Iterator);
	FVector2D GetPosition(FIntVector2 Point, FShape& Shape) const;

	bool GetMousePosition(FVector2D& Position);

	//FVector2D GetMousePosition();

	//bool GetShape(FShape*& Shape, int32 Index);
	//bool GetPoint(FVector2D& Position, FShape*& Shape, int32 Index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridWidthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DotWidthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMagicSkill*> Spells;


protected:
	//UPROPERTY()
	//FVector2D StartPos;
	//UPROPERTY()
	//FVector2D EndPos;
	UPROPERTY()
	FVector2D MousePos;
	//UPROPERTY()
	//TArray<FVector2D> LineArray;
	//UPROPERTY()
	//TArray<FVector2D> DotArray;
	//UPROPERTY()
	TDeque<FShape> Shapes;
	UPROPERTY()
	//map between dot position and number of reference count
	TMap<FIntVector2, uint64> ShownDots;
	UPROPERTY()
	bool bIsDrawing = false;


private:
	void TickDotCollision();
	FIntVector2 CheckDotsAroundCollsion(FIntVector2 LineStart);
	bool CheckDotLineCollsion(FIntVector2 LineStart, FIntVector2 DotPos, FVector2D StartPos);
	void TickShapeRecognizer();
	bool IsShapeEqual(TArray<FIntVector2>& CurrShape, UMagicSkill& Spell);
	void AddDotSquare(FIntVector2 Pos);
	void RemoveDotSquare(FIntVector2 Pos);


	//protected:
	//	// Called when the game starts
	//	virtual void BeginPlay() override;
	//
	//public:	
	//	// Called every frame
	//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
