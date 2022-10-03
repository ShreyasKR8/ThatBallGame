// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EnemySphere.generated.h"

/**
 * 
 */

class UCapsuleComponent;

UCLASS()
class THATBALLGAME_API AEnemySphere : public AStaticMeshActor
{
	GENERATED_BODY()

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* EnemySphereMesh;

    UPROPERTY(VisibleAnywhere)
    float RunningTime;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float DistanceFactor =  100.0f;

public:

    AEnemySphere();

    virtual void Tick(float DeltaTime) override;

};
