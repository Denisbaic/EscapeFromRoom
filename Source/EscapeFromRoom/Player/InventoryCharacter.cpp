// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "Inventory/Interactable.h"
#include "Inventory/AutoPickup.h"
#include "Inventory/InvItem.h"
#include "Player/EscapeFromRoomPlayerController.h"

// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a FirstPerson came
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
	FirstPersonCamera->bUsePawnControlRotation = true;

	FirstPersonCamera->bAutoActivate = false;

	//Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(FName("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);
}


void AInventoryCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInventoryCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AInventoryCharacter::ChangeCamera()
{
	if(FollowCamera->IsActive())
	{
		GetMesh()->SetVisibility(false);
		FollowCamera->SetActive(false);
		FirstPersonCamera->SetActive(true);
	}
	else
	{		
		GetMesh()->SetVisibility(true);
		FollowCamera->SetActive(true);
		FirstPersonCamera->SetActive(false);
	}
}

// Called when the game starts or when spawned
void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInventoryCharacter::CollectAutoPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(GetController());

	// For each collected Actor
	for (const auto& ActorCollected: CollectedActors)
	{
		// Cast the actor to AAutoPickup
		AAutoPickup* const TestPickup = Cast<AAutoPickup>(ActorCollected);
		// If the cast is successful and the pickup is valid and active 
		if (TestPickup && !TestPickup->IsPendingKill())
		{
			TestPickup->Collect(PlayerController);
		}
	}

}

void AInventoryCharacter::CheckForInteractables()
{
	// Create a LineTrace to check for a hit
	FHitResult HitResult;

	int32 Range = 500;
	FVector StartTrace = FollowCamera->GetComponentLocation();
	FVector EndTrace = (FollowCamera->GetForwardVector() * Range) + StartTrace;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AEscapeFromRoomPlayerController* PlayerController = Cast<AEscapeFromRoomPlayerController>(GetController());

	if (PlayerController)
	{
		// Check if something is hit
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			// Cast the actor to AInteractable
			AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());
			// If the cast is successful
			if (Interactable)
			{
				PlayerController->CurrentInteractable = Interactable;
				return;
			}
		}

		PlayerController->CurrentInteractable = nullptr;
	}
}

// Called every frame
void AInventoryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollectAutoPickups();
	CheckForInteractables();
}

// Called to bind functionality to input
void AInventoryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("ChangeCamera", IE_Pressed, this, &AInventoryCharacter::ChangeCamera);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInventoryCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInventoryCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

