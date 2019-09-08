// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoPickup.h"
#include "Player/EscapeFromRoomPlayerController.h"

AAutoPickup::AAutoPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");
}

void AAutoPickup::Collect_Implementation(APlayerController* Controller)
{
	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(Controller);

	if (PlayerController->AddItemToInventoryByID(ItemID))
		Destroy();
}

FName AAutoPickup::GetItemID()
{
	return ItemID;
}