// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Playground_511/Playground_511.h"
#include "ReubGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_511_API UReubGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UReubGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EReubTestAbilityInputID AbilityInputID = EReubTestAbilityInputID::None;
};
