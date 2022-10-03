// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySphere.h"
#include "Components/CapsuleComponent.h"


AEnemySphere::AEnemySphere()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
    
    RootComponent = CapsuleComp;

    EnemySphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySphereMesh"));
    EnemySphereMesh->SetupAttachment(RootComponent);

}

void AEnemySphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
    float DeltaDistance = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.X += DeltaDistance * DistanceFactor;
    RunningTime += DeltaTime;
    SetActorLocation(NewLocation);

}
