// Fill out your copyright notice in the Description page of Project Settings.


#include "CombLockButton.h"
#include "Components/StaticMeshComponent.h"
#include "CombLock.h"


ACombLockButton::ACombLockButton()
{
	//ClickedMesh = CreateDefaultSubobject<UStaticMeshComponent>("ClickedMesh");
	//RootComponent = Cast<USceneComponent>(ClickedMesh);
	CodeContained = "";
	ButtonFunction = EButtonFunction::AddText;
}

void ACombLockButton::Interact_Implementation(APlayerController* Controller)
{
	if(GetAttachParentActor())
	{
		ACombLock* CombLockPtr = Cast<ACombLock>(GetAttachParentActor());
		switch (ButtonFunction)
		{
		case  EButtonFunction::AddText:CombLockPtr->AddToScreen(CodeContained); break;
		case EButtonFunction::Compare: CombLockPtr->Compare(); break;
		case EButtonFunction::DeleteAll: CombLockPtr->DeleteAll(); break;
		case EButtonFunction::DeleteLast:CombLockPtr->DeleteLast(); break;
		}
	
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Button %s return %s"), *GetName(), *CodeContained);
	UE_LOG(LogTemp, Warning, TEXT("Button %s owned by %s"), *GetName(), *GetAttachParentActor()->GetName());
}

