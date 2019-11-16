// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Projectile.h"


UTurretComponent::UTurretComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTurretComponent::Fire()
{
	if (!ensure(Trunk)) { return; }

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(Bullet,
		Trunk->GetSocketLocation(FName("Trunk")),
		Trunk->GetSocketRotation(FName("Trunk")));
	Projectile->LaunchProjectile(ProjectileSpeed);
}

// Called when the game starts
void UTurretComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurretComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

