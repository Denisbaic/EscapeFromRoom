// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/GameStateBase.h"
#include "EscapeFromRoomGameState.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEFROMROOM_API AEscapeFromRoomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AEscapeFromRoomGameState();

	UDataTable* GetItemDB() const;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemDB;
};
