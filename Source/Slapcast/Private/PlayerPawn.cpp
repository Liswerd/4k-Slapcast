// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	
	
	//Root = CreateDefaultSubobject<USceneComponent>("Root");
	//SetRootComponent(Root);
	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	RootComponent = Collision;   //CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	Mesh->SetupAttachment(RootComponent);
	//Collision->SetupAttachment(RootComponent);
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::Move(const FInputActionValue& InputActionValue)
{

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	//Get control rotation
	const FRotator ControlRotation = GetControlRotation();

	//Isolate the yaw
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);
	//Get forward vector	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//Get right vector
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	//Move the character
	if (Mesh)
	{
		AddMovementInput(ForwardDirection, InputAxisVector.Y);
		AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

