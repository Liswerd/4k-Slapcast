// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "EnhancedInputLibrary.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

//#include <SkeletalMeshAdapter.h>
//#include <Engine/SkeletalMeshComponent.h>
#include "MagicComponent.h"

#include "PlayerPawn.generated.h"


UCLASS()
class SLAPCAST_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to move the player
	void Move(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick Cast Move"))
	void ExecMove(FVector2D Position);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Magic Spell"))
	void ExecAddMagicSpell(UMagicSkill* Spell) {
		Magic->Spells.Push(Spell);
	}

	FVector GetVelocity() const override {
		return PawnMovement->Velocity;
	}

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMagicComponent* Magic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UFloatingPawnMovement* PawnMovement;

};
