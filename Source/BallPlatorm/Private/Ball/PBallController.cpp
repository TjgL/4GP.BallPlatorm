// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/PBallController.h"
#include "EnhancedInputComponent.h"
#include "Ball/PBall.h"

void APBallController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputContext, 0);
	}
}

void APBallController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Ball = CastChecked<APBall>(InPawn);
}

void APBallController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APBallController::MoveBall);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APBallController::Jump);
	}
}

void APBallController::MoveBall(const FInputActionValue& Value)
{
	FVector2D MoveDirection = Value.Get<FVector2D>();
	
	if (!MoveDirection.IsZero())
		Ball->Move(MoveDirection);
}

void APBallController::Jump(const FInputActionValue& Value)
{
	Ball->Jump(); 
}

