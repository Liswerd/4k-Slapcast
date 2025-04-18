// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MagicSkill.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SLAPCAST_API AMagicSkill : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> Shape;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnCast"))
	void RecieveCast(FVector2D start, FVector2D end);

};
