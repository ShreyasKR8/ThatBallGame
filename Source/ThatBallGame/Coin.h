// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class UCapsuleComponent;
class ABallBase;
UCLASS()
class THATBALLGAME_API ACoin : public AActor
{
	GENERATED_BODY()
	
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CoinMesh;

    UPROPERTY(EditAnywhere, Category = "Rotations")
    float YawRotateAmount = 5.f;

    UPROPERTY(VisibleAnywhere)
    ABallBase* PlayerBall;

    UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* CoinCollectSound;

    void RotateCoin();

    void Impulse();

    void AddScore();
public:	
	// Sets default values for this actor's properties
	ACoin();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionTrigger;

    UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

};
