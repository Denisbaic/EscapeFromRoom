// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeFromRoomPlayerController.h"
#include "EscapeFromRoomGameState.h"
//#include "InventoryCharacter.h"

AEscapeFromRoomPlayerController::AEscapeFromRoomPlayerController()
{
	InventorySlotLimit = 50;
	InventoryWeightLimit = 500;
}

int32 AEscapeFromRoomPlayerController::GetInventoryWeight()
{
	
	int32 Weight = 0;
	
	for (auto& Item : Inventory)
	{
		Weight += Item.Weight;
	}
	
	return Weight;
}

bool AEscapeFromRoomPlayerController::AddItemToInventoryByID(FName ID)
{
	
	AEscapeFromRoomGameState* GameState = Cast<AEscapeFromRoomGameState>(GetWorld()->GetGameState());
	UDataTable* ItemTable = GameState->GetItemDB();
	
	FInvItem* ItemToAdd = ItemTable->FindRow<FInvItem>(ID, "");

	if (ItemToAdd)
	{
		if (Inventory.Num() < InventorySlotLimit && GetInventoryWeight() + ItemToAdd->Weight <= InventoryWeightLimit)
		{
			Inventory.Add(*ItemToAdd);
			ReloadInventory();
			return true;
		}
	}
	
	return false;
}

void AEscapeFromRoomPlayerController::Interact()
{
	
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
	
}

void AEscapeFromRoomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &AEscapeFromRoomPlayerController::Interact);
}