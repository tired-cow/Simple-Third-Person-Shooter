// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
	: SceneComponent{ CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")) },
	SkeletalMeshComponent{ CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent")) },
	MaxRange{ 1000.0f },
	Damage{ 10.0f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = SceneComponent;
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Fire()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));
	
	APawn* OwnerPawn{ Cast<APawn>(GetOwner()) };
	if (OwnerPawn == nullptr)
		return;
	
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) 
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End{ Location + Rotation.Vector() * MaxRange };

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool Success{ GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params) };

	if (Success)
	{
		FVector ShotDirection{ -Rotation.Vector() };
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		if (Hit.GetActor())
		{
			FPointDamageEvent DamageEvent{ Damage, Hit, ShotDirection, nullptr };
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}