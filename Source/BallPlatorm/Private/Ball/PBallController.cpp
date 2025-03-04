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
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APBallController::Look);
	}
}

void APBallController::MoveBall(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>();
	
	if (!MoveDirection.IsZero())
	{
		FRotator Rotation = GetControlRotation();

		Rotation.Pitch = 0;
		Rotation.Roll = 0;

		const FVector ForwardVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		const FVector MoveInput = (ForwardVector * MoveDirection.Y + RightVector * MoveDirection.X);
		
		Ball->Move(MoveInput);
	}
}

void APBallController::Jump(const FInputActionValue& Value)
{
	Ball->Jump(); 
}

void APBallController::Look(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();

	if (!Input.IsZero())
	{
		AddYawInput(Input.X);
		AddPitchInput(Input.Y);
	}
}

