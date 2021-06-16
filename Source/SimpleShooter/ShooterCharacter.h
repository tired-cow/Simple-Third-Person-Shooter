// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	void MoveForward(float);
	void MoveRight(float);
	void LookUpRate(float);
	void LookRightRate(float);

	UPROPERTY(EditAnywhere)
	float RotationRate;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;
	
	UPROPERTY(VisibleAnywhere)
	float Health;
	
	UPROPERTY()
	AGun* Gun;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Shoot();
};
