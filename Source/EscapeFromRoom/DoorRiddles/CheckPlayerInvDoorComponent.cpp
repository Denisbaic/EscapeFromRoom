// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPlayerInvDoorComponent.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "Player/EscapeFromRoomPlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerPawn.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCheckPlayerInvDoorComponent::UCheckPlayerInvDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCheckPlayerInvDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	this->TriggerVolume->OnActorBeginOverlap.AddDynamic(this, &UCheckPlayerInvDoorComponent::CheckInventory);
}

void UCheckPlayerInvDoorComponent::CheckInventory(AActor* OverlappedActor, AActor* OtherActor)
{
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);

	if(!PlayerCharacter)
	{
		return;
	}
		
	//AEscapeFromRoomPlayerController* PlayerController= Cast<AEscapeFromRoomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(PlayerCharacter->GetController());
	for (FInvItem InvItem : PlayerController->Inventory)
	{
		if(InvItem.ItemID==ItemId)
		{
			DoorOpenEvent.Broadcast();
			return;
		}
	}
}


// Called every frame
void UCheckPlayerInvDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}