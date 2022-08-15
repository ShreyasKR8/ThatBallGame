// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(RootComponent);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(BallMesh);
    SpringArm->SetUsingAbsoluteRotation(true); /* Sets the value of bAbsoluteRotation without causing other side effects to this instance. */
    SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f)); /* Set the rotation of the component relative to its parent. */

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false; /* We don't want the controller rotating the camera */

    RollTorque = 5000000.0f;
}

// Called when the game starts or when spawned
void ABallBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Score = %d"), Score)

}

// Called to bind functionality to input
void ABallBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABallBase::MoveForward);
    PlayerInputComponent->BindAxis("MoveLeft", this, &ABallBase::MoveLeft);

}

void ABallBase::MoveForward(float Val)
{
    const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
    BallMesh->AddTorqueInRadians(Torque);
}

void ABallBase::MoveLeft(float Val) 
{
    const FVector Torque = FVector(Val * RollTorque, 0.f, 0.f);
    BallMesh->AddTorqueInRadians(Torque);
}