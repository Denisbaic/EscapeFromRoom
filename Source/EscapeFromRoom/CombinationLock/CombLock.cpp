// Fill out your copyright notice in the Description page of Project Settings.


#include "CombLock.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "CombLockButton.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include <iostream>
// Sets default values
ACombLock::ACombLock()
{
	//////
	std::ifsteam a;
	
	//////
	PrimaryActorTick.bCanEverTick = true;
	CombLockMesh = CreateDefaultSubobject<UStaticMeshComponent>("CombLockMesh");
	//Screen= CreateDefaultSubobject<ATextRenderActor>("Screen");

	RootComponent = Cast<USceneComponent>(CombLockMesh);
	//Screen->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

bool ACombLock::Compare_Implementation()
{
	return ScreenText->Text.ToString() == LockCode;
}

void ACombLock::DeleteLast_Implementation()
{
	auto TempString = ScreenText->Text.ToString();
	TempString.RemoveAt(0);
	ScreenText->SetText(FText::FromString(TempString));
}

void ACombLock::DeleteAll_Implementation()
{
	ScreenText->SetText(FText::FromString(""));
}

void ACombLock::AddToScreen_Implementation(FString& String)
{
	if(!ScreenText)
		return;
	ScreenText->SetText(FText::FromString(String+ScreenText->Text.ToString()));
}

// Called when the game starts or when spawned
void ACombLock::BeginPlay()
{
	Super::BeginPlay();
	
	FString BaseSocketName = "ButtonPlace_";
	FTransform SocketTransfrom;
	UStaticMeshSocket const* SocketPtr;
	for(int32 i=0; i<ButtonCount;i++)
	{
		const FName SocketName = FName(*(BaseSocketName + FString::FromInt(i)));
		 SocketPtr = CombLockMesh->GetSocketByName(SocketName);
		if(SocketPtr)
		{
			SocketPtr->GetSocketTransform(SocketTransfrom, CombLockMesh);
			ACombLockButton* CreatedButton = GetWorld()->SpawnActorDeferred<ACombLockButton>(ButtonType, SocketTransfrom,  GetOwner());
			if (!CreatedButton)
				return;
			CreatedButton->AttachToComponent(CombLockMesh, FAttachmentTransformRules::KeepWorldTransform);
			CreatedButton->CodeContained = FString::FromInt(i);
			CreatedButton->ButtonFunction = EButtonFunction::AddText;
			UGameplayStatics::FinishSpawningActor(CreatedButton, SocketTransfrom);
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Your StaticMesh doesn't have socket with name: %s !"),(*(BaseSocketName + FString::FromInt(i))))
		}
	}
	SocketPtr = CombLockMesh->GetSocketByName(*(BaseSocketName+"-"));
	if(SocketPtr)
	{
		SocketPtr->GetSocketTransform(SocketTransfrom, CombLockMesh);
		ACombLockButton* CreatedButton = GetWorld()->SpawnActorDeferred<ACombLockButton>(ButtonType, SocketTransfrom, GetOwner());
		if (!CreatedButton)
			return;
		CreatedButton->AttachToComponent(CombLockMesh, FAttachmentTransformRules::KeepWorldTransform);
		CreatedButton->CodeContained = "<-";
		CreatedButton->ButtonFunction = EButtonFunction::DeleteLast;
		UGameplayStatics::FinishSpawningActor(CreatedButton, SocketTransfrom);
	}
	SocketPtr = CombLockMesh->GetSocketByName(*(BaseSocketName + "--"));
	if (SocketPtr)
	{
		SocketPtr->GetSocketTransform(SocketTransfrom, CombLockMesh);
		ACombLockButton* CreatedButton = GetWorld()->SpawnActorDeferred<ACombLockButton>(ButtonType, SocketTransfrom, GetOwner());
		if (!CreatedButton)
			return;
		CreatedButton->AttachToComponent(CombLockMesh, FAttachmentTransformRules::KeepWorldTransform);
		CreatedButton->CodeContained = "<--";
		CreatedButton->ButtonFunction = EButtonFunction::DeleteAll;
		UGameplayStatics::FinishSpawningActor(CreatedButton, SocketTransfrom);
	}
	SocketPtr = CombLockMesh->GetSocketByName(*(BaseSocketName + "="));
	if (SocketPtr)
	{
		SocketPtr->GetSocketTransform(SocketTransfrom, CombLockMesh);
		ACombLockButton* CreatedButton = GetWorld()->SpawnActorDeferred<ACombLockButton>(ButtonType, SocketTransfrom, GetOwner());
		if (!CreatedButton)
			return;
		CreatedButton->AttachToComponent(CombLockMesh, FAttachmentTransformRules::KeepWorldTransform);
		CreatedButton->CodeContained = "=";
		CreatedButton->ButtonFunction = EButtonFunction::Compare;
		UGameplayStatics::FinishSpawningActor(CreatedButton, SocketTransfrom);
	}
}

// Called every frame
void ACombLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

