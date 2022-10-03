// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallBase.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class THATBALLGAME_API ABallBase : public APawn
{
	GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* Camera;

    /* Torque to apply when trying to roll the ball */
    UPROPERTY(EditAnywhere, Category = BallPhysics)
    float RollTorque;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f;

    UPROPERTY(EditAnywhere, Category = BallPhysics)
    float JumpImpulse;

    //For avoiding double jumps
    bool bCanJump;

    void LookLeftRightRate(float AxisValue);

    void LookUpDownRate(float AxisValue);

    //To set bCanJump to true upon hitting the floor
    void NotifyHit(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp,
        bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit);


public:
	// Sets default values for this pawn's properties
	ABallBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, Category = "Score")
    int32 Score = 0;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    /* To be called in SetupPlayerInputComponent to move the ball forward or backward */
    void MoveForward(float Val);

    /* To be called in SetupPlayerInputComponent to move the ball left or right */
    void MoveLeft(float Val);

    /* To be called in SetupPlayerInputComponent to move the ball up */
    void Jump();

};