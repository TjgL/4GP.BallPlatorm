// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "PBallController.generated.h"

class APBall;

/**
 * 
 */
UCLASS()
class BALLPLATORM_API APBallController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void MoveBall(const FInputActionValue& Value);

	UFUNCTION()
	void Jump(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LookAction;

private:
	TObjectPtr<APBall> Ball;
};
