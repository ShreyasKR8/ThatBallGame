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

    Movement(DeltaTime);

}

void AEnemySphere::Movement(float DeltaTime) //Oscillate in X axis or Z axis
{
    FVector NewLocation = GetActorLocation();
    float DeltaDistance = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

    if(MoveHorizontal)  //Move horizontal can be set in the editor
    {
        NewLocation.X += DeltaDistance * DistanceFactor;
    }
    else
    {
        NewLocation.Z += DeltaDistance * DistanceFactor;
    }

    RunningTime += DeltaTime;
    SetActorLocation(NewLocation);
}
