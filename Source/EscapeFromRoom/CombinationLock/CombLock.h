// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombLock.generated.h"

class UTextRenderComponent;
class ACombLockButton;
UCLASS()
class ESCAPEFROMROOM_API ACombLock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombLock();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ButtonCount=10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<ACombLockButton> ButtonType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UStaticMeshComponent* CombLockMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextRenderComponent* ScreenText;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FString LockCode;

	UFUNCTION(BlueprintNativeEvent)
		bool Compare();
	virtual bool Compare_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void DeleteAll();
	virtual void DeleteAll_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void DeleteLast();
	virtual void DeleteLast_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void AddToScreen(FString& String);
	virtual void AddToScreen_Implementation(FString& String);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
