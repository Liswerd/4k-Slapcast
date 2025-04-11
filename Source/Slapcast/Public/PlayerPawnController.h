// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputLibrary.h"
#include "MagicHUD.h"

#include "PlayerPawnController.generated.h"

/**
 *
 */
UCLASS()
class SLAPCAST_API APlayerPawnController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputMappingContext* InputMappingContext;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hud")
	AMagicHUD* MagicHud;*/

private:
	// called when button pressed
	void Move(const FInputActionValue& InputActionValue);
	void SetupInputComponent();
};
