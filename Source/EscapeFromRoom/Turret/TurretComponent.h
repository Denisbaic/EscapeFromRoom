// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretComponent.generated.h"

class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEFROMROOM_API UTurretComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretComponent();
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed=200.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AProjectile> Bullet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Trunk;
	UFUNCTION(BlueprintCallable)
		void Fire();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
