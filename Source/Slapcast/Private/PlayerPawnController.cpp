// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"
#include "EnhancedInputSubSystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerPawn.h"
//#include "MagicGameState.h"


void APlayerPawnController::BeginPlay()
{
	//Call the superclass method for BeginPlay() so Unreal knows to include this as part of the list of objects doing stuff
	Super::BeginPlay();
	this->SetShowMouseCursor(true);

	//Get a pointer to the EnhancedInputSubsystem
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	//Add the IMC to the EnhancedInputSubsystem
	//if (EnhancedInputSubsystem) {
	EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);
	//}
}

void APlayerPawnController::Tick(float DeltaSeconds)
{
	//AMagicGameState* GameState = GetWorld()->GetGameState<AMagicGameState>();
	APlayerPawn* PlayerPawn = GetPawn<APlayerPawn>();
	FVector2D MousePos;
	// if mouse is on screen, tick Gamestate
	if (GetMousePosition(MousePos.X, MousePos.Y)) {
		PlayerPawn->Magic->TickPoint(MousePos / GetHUD<AMagicHUD>()->GetWidth());
		PlayerPawn->ExecMove(MousePos / GetHUD<AMagicHUD>()->GetWidth());

	}
}

void APlayerPawnController::SetupInputComponent()
{
	//Access super class to connect input
	Super::SetupInputComponent();

	//Get a pointer to the EnhancedInputComponent our PlayerController now has
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//Bind the MoveAction to the Move method
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawnController::Move);
	//EnhancedInputComponent->BindAction(MouseAction, ETriggerEvent::Triggered, this, &APlayerPawnController::MouseMove);
	EnhancedInputComponent->BindAction(ButtonAction, ETriggerEvent::Triggered, this, &APlayerPawnController::Click);
}

void APlayerPawnController::Move(const FInputActionValue& InputActionValue)
{
	APlayerPawn* ControlPawn = GetPawn<APlayerPawn>();

	ControlPawn->Move(InputActionValue);
}

void APlayerPawnController::MouseMove(const FInputActionValue& InputActionValue)
{
	//AMagicGameState* GameState=GetWorld()->GetGameState<AMagicGameState>();
	//FVector2D MousePos = InputActionValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("mouse pos: %f %f"), MousePos.X, MousePos.Y);
	//GameState->TickPoint(MousePos / GetHUD<AMagicHUD>()->GetCanvasWidth());

}

void APlayerPawnController::Click(const FInputActionValue& InputActionValue)
{
	//AMagicGameState* GameState = GetWorld()->GetGameState<AMagicGameState>();
	UMagicComponent* MagicComponent = GetPawn<APlayerPawn>()->Magic;
	bool is_down = InputActionValue.Get<bool>();
	//UE_LOG(LogTemp, Warning, TEXT("moise down: %i"), is_down);
	if (is_down) {
		FHitResult HitResult;
		bool test = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, HitResult);
		UE_LOG(LogTemp, Warning, TEXT("Hit result: %s %i"), *HitResult.ImpactPoint.ToString(), test);
		MagicComponent->StartDraw(HitResult.ImpactPoint);
	}
	else {
		MagicComponent->EndDraw();
	}
}
