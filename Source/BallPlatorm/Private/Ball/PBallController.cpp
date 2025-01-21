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
		Input->BindAction(MoveAction, ETriggerEvent::Started, this, &APBallController::MoveBall);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &APBallController::Jump);
	}
}

void APBallController::MoveBall(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "MoveBall");
}

void APBallController::Jump(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Jump");
}

