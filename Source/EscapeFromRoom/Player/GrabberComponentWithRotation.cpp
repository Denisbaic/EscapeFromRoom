// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponentWithRotation.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PlayerPawn.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"

UGrabberComponentWithRotation::UGrabberComponentWithRotation()
{
	
}

void UGrabberComponentWithRotation::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRotationMode && PhysicsHandle->GetGrabbedComponent())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), (this->bRotationMode ? TEXT("True") : TEXT("False")));
		//const FRotator DeltaRotator = GetOwner()->GetActorRotation() - RotatorInBeginI;
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *DeltaRotator.ToString());
		//PhysicsHandle->GetGrabbedComponent()->AddLocalRotation(DeltaRotator);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *PhysicsHandle->GetGrabbedComponent()->GetName());
		//GetOwner()->SetActorRotation(RotatorInBeginI);
		auto Owner = Cast<APlayerPawn>(GetOwner())->GetController();

		FRotator TargetRotator;
		FVector TargetLoc;
		PhysicsHandle->GetTargetLocationAndRotation(TargetLoc, TargetRotator);
		auto ResultRotator = TargetRotator + (Owner->GetControlRotation() - RotatorInBeginI);

		/*
		if(FMath::IsNearlyEqual(FMath::Abs(ResultRotator.Yaw),90.f,0.2f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Yaw nearly 90"));
			//ResultRotator.Yaw *= -1;
			ResultRotator.Yaw > 0.f ? ResultRotator.Yaw = 100.f : ResultRotator.Yaw =-100.f;
		}
		if (FMath::IsNearlyEqual(FMath::Abs(ResultRotator.Pitch), 90.f, 0.2f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Pitch nearly 90"));
			//ResultRotator.Pitch *= -1;
			ResultRotator.Pitch > 0.f ? ResultRotator.Pitch = 100.f : ResultRotator.Pitch = -100.f;
			//ResultRotator.Pitch += 360.f;
			//ResultRotator.Roll *= -1;
			//ResultRotator.Pitch > 0.f ? ResultRotator.Pitch -= ResultRotator.Pitch *2 : ResultRotator.Pitch += ResultRotator.Pitch *2;
		}
		if (FMath::IsNearlyEqual(FMath::Abs(ResultRotator.Roll), 90.f, 0.2f))
		{
			UE_LOG(LogTemp, Warning, TEXT("Roll nearly 90"));
			//ResultRotator.Roll *= -1;
			//ResultRotator.Roll > 0.f ? ResultRotator.Roll *=-1 : ResultRotator.Roll += ResultRotator.Roll * 2;
			ResultRotator.Roll > 0.f ? ResultRotator.Roll = 100.f : ResultRotator.Roll = -100.f;
		}
		*/
		PhysicsHandle->SetTargetRotation(TargetRotator);
		
		UE_LOG(LogTemp,Warning,TEXT("%s"),*TargetRotator.ToString())
		Owner->SetControlRotation(RotatorInBeginI);
		//PhysicsHandle->GetGrabbedComponent()->AddLocalRotation(FRotator(Owner->BaseLookUpRate,Owner->BaseTurnRate,0.f));
		//Owner->BaseLookUpRate -= Owner->BaseLookUpRate;
		//Owner->BaseTurnRate -= Owner->BaseTurnRate;
	}
}

void UGrabberComponentWithRotation::RotationMode()
{
	if(PhysicsHandle->GetGrabbedComponent())
	{
		bRotationMode = !bRotationMode;
		const auto Owner = Cast<APlayerPawn>(GetOwner())->GetController();
		RotatorInBeginI = Owner->GetControlRotation();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), (this->bRotationMode ? TEXT("True") : TEXT("False")));
	}
	
}

void UGrabberComponentWithRotation::SetupInputComponent()
{
	Super::SetupInputComponent();
	GetOwner()->InputComponent->BindAction("RotateItem", IE_Pressed, this, &UGrabberComponentWithRotation::RotationMode);
	GetOwner()->InputComponent->BindAction("RotateItem", IE_Released, this, &UGrabberComponentWithRotation::RotationMode);
}

void UGrabberComponentWithRotation::Release()
{
	bRotationMode = false;
	Super::Release();
}
