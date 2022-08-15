// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BallBase.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    // RootComponent = CapsuleComp;

    CollisionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
    CollisionTrigger->SetBoxExtent(FVector(100.f, 100.f,100.f));
	SetRootComponent(CollisionTrigger);

    CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    CoinMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

    CoinMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	CoinMesh->OnComponentEndOverlap.AddDynamic(this, &ACoin::OnOverlapEnd);

	CollisionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	CollisionTrigger->OnComponentEndOverlap.AddDynamic(this, &ACoin::OnOverlapEnd);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RotateCoin();
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor && (OtherActor != this) && OtherComp)
    {
        AddScore();
        UGameplayStatics::PlaySoundAtLocation(this, CoinCollectSound, GetActorLocation());
    }
}

void ACoin::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ACoin::RotateCoin()
{
    FRotator Rotation = FRotator(0.f, YawRotateAmount, 0.f);
    AddActorWorldRotation(Rotation);
    // AddActorLocalRotation(Rotation);
}

void ACoin::AddScore() //Called from OnOverlapBegin()
{
    PlayerBall = Cast<ABallBase>(UGameplayStatics::GetPlayerPawn(this, 0));
    if(PlayerBall)
    {
        PlayerBall->Score += 1;
        UE_LOG(LogTemp, Warning, TEXT("Score = %d"), PlayerBall->Score)
        Destroy();
    }
}