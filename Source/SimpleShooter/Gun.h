// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
		float MaxRange;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;
	UPROPERTY(EditAnywhere)
		float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();
};
