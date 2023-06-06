// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

/******************************************************************************/
// Added Code to Character (Gameplay Ability System)
/******************************************************************************/

#include "GameplayAbilities/Public/AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>

/******************************************************************************/
// End of Code Added
/******************************************************************************/

#include "InputActionValue.h"
#include "Playground_511Character.generated.h"


UCLASS(config=Game)
class APlayground_511Character : public ACharacter, /* Added Code to Character (Gameplay Ability System) */ public IAbilitySystemInterface /* End of Code Added */
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/******************************************************************************/
	// Added Code to Character (Gameplay Ability System)
	/******************************************************************************/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = "true"))
	class UReubAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UReubAttributeSet* Attributes;

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

public:
	APlayground_511Character();

	/******************************************************************************/
	// Added Code to Character (Inventory System)
	/******************************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Armor;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItems* Item);

	/** Inventory System */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UReubInventoryComponent* Inventory;

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/
	
	/******************************************************************************/
	// Added Code to Character (Parkour Movement System)
	/******************************************************************************/

	/** Parkour System */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour")
	class UParkourMovementComponent* ParkourMovementSystem;

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

	/******************************************************************************/
	// Added Code to Character (Gameplay Ability System)
	/******************************************************************************/

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/**Effect that initializes our default attributes. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	/**Effect that initializes our default attributes. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UReubGameplayAbility>> DefaultAbilities;

	/******************************************************************************/
	// End of Code Added
	/******************************************************************************/

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

