// Copyright Epic Games, Inc. All Rights Reserved.

#include "Playground_511Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

/******************************************************************************/
// Added Code to Character (Inventory System Component)
/******************************************************************************/

#include "InventorySystem/Items.h"
#include "InventorySystem/ReubInventoryComponent.h"

/******************************************************************************/
// End of Code Added
/******************************************************************************/

/******************************************************************************/
// Added Code to Character (Parkour Movement System)
/******************************************************************************/

#include "ParkourSystem/ParkourMovementComponent.h"

/******************************************************************************/
// End of Code Added
/******************************************************************************/

/******************************************************************************/
// Added Code to Character (Inventory System Component)
/******************************************************************************/

#include "AbilitySystem/ReubAttributeSet.h"
#include "AbilitySystem/ReubAbilitySystemComponent.h"
#include "AbilitySystem/ReubGameplayAbility.h"
#include <GameplayEffectTypes.h>

/******************************************************************************/
// End of Code Added
/******************************************************************************/

//////////////////////////////////////////////////////////////////////////
// APlayground_511Character

APlayground_511Character::APlayground_511Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	/******************************************************************************/
	// Added Code to Character (Inventory System Component)
	/******************************************************************************/

	Inventory = CreateDefaultSubobject<UReubInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	Health = 100.f;
	Armor = 0.f;

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/


	/******************************************************************************/
	// Added Code to Character (Parkour Movement System)
	/******************************************************************************/

	ParkourMovementSystem = CreateDefaultSubobject<UParkourMovementComponent>("Parkour Movement");

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

	/******************************************************************************/
	// Added Code to Character (Gameplay Ability System)
	/******************************************************************************/

	AbilitySystemComponent = CreateDefaultSubobject<UReubAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UReubAttributeSet>("Attributes");

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

/******************************************************************************/
// Added Code to Character (Inventory System Component)
/******************************************************************************/

void APlayground_511Character::UseItem(class UItems* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); //BP Event
	}
}

/******************************************************************************/
// End of Code Added
/******************************************************************************/

/******************************************************************************/
// Added Code to Character (Gameplay Ability System)
/******************************************************************************/

UAbilitySystemComponent* APlayground_511Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayground_511Character::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void APlayground_511Character::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UReubGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					StartupAbility,
					1,
					static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),
					this));
		}
	}
}

void APlayground_511Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server GAS Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void APlayground_511Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Client GAS Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();

	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EReubTestAbilityInputID", static_cast<int32>(EReubTestAbilityInputID::Confirm), static_cast<int32>(EReubTestAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

/******************************************************************************/
// End of Code Added
/******************************************************************************/

void APlayground_511Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	/******************************************************************************/
	// Added Code to Character (Parkour Movement System)
	/******************************************************************************/

	ParkourMovementSystem->Initialize(this);

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayground_511Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayground_511Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayground_511Character::Look);

	}

	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EReubTestAbilityInputID", static_cast<int32>(EReubTestAbilityInputID::Confirm), static_cast<int32>(EReubTestAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}

}

void APlayground_511Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayground_511Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




