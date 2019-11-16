// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;
class UGameplayStatics;

UCLASS()
class ESCAPEFROMROOM_API AProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(EditAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(EditAnywhere, Category = "Components")
		URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float DelayToDestroy = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileDamage = 20.f;
public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void LaunchProjectile(float Speed);

private:

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;


	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyDelay();

};
