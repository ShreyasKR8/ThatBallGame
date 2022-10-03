// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMathLibrary.inl"

#define PRINT_DEBUG(Message) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,  FString(__FUNCTION__) + "(" + FString::FromInt(__LINE__) + ") " + Message); 

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

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
	// Camera->bUsePawnControlRotation = true; /* We want the controller rotating the camera */

    // RollTorque = 5000000.0f;
    RollTorque = 50000.0f;
    // RollTorque = ( DestinationRotation - CurrentRotation ) * 0.1f; (or an other factoring number)
    JumpImpulse = 35000.0f;
    bCanJump = true;
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

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABallBase::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &ABallBase::MoveLeft);
    PlayerInputComponent->BindAxis(TEXT("LookLeft/Right"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookLeft/RightRate"), this, &ABallBase::LookLeftRightRate);
    PlayerInputComponent->BindAxis(TEXT("LookUp/Down"), this, &ABallBase::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookUp/DownRate"), this, &ABallBase::LookUpDownRate);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABallBase::Jump);

}

void ABallBase::MoveForward(float Val)
{
    const FVector Force = Camera->GetForwardVector() * Val * RollTorque;
    BallMesh->AddForce(Force);
}

void ABallBase::MoveLeft(float Val) 
{
    const FVector Force = Camera->GetRightVector() * Val * RollTorque;
    BallMesh->AddForce(Force);
}

void ABallBase::Jump()
{
    if(bCanJump)
    {
        const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
        BallMesh->AddImpulse(Impulse);
        bCanJump = false;
    }
}

void ABallBase::LookLeftRightRate(float AxisValue)
{
    //Using GetDeltaSeconds() to damp controller movement speed.
    AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABallBase::LookUpDownRate(float AxisValue) 
{
    //Using GetDeltaSeconds() to damp controller movement speed.
    AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABallBase::NotifyHit(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp,
        bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    bCanJump = true;
}
