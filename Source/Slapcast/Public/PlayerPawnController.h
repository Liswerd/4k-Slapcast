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

public:
		virtual void Tick(float DeltaSeconds)override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputAction* ButtonAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputAction* MouseAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs")
	UInputMappingContext* InputMappingContext;

private:
	// called when button pressed
	void SetupInputComponent() override;
	void Move(const FInputActionValue& InputActionValue);
	void MouseMove(const FInputActionValue& InputActionValue);
	void Click(const FInputActionValue& InputActionValue);

};

