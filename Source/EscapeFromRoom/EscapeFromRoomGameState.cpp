// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeFromRoomGameState.h"

AEscapeFromRoomGameState::AEscapeFromRoomGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
	ItemDB = BP_ItemDB.Object;
}

UDataTable* AEscapeFromRoomGameState::GetItemDB() const
{
	return ItemDB;
}