// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PBall.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;
class UPBallMovementComponent;

UCLASS()
class BALLPLATORM_API APBall : public APawn
{
	GENERATED_BODY()

public:
	APBall();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Jump() const;
	void Move(const FVector2D MoveDirection) const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ball", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> BallMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ball", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPBallMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ball", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ball", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
};
