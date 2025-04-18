// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MagicComponent.generated.h"


UCLASS( )
class SLAPCAST_API UMagicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	//UMagicComponent();
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

//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
