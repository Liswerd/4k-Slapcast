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

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFloatingPawnMovement* PawnMovement;

};
