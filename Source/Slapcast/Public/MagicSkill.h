// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "MagicSkill.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class SLAPCAST_API UMagicSkill : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntPoint> Shape;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnCast"))
	void ExecCast(FVector start, FVector end);

};
