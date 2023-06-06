// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "CardItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_511_API ACardItemActor : public AItemActor
{
	GENERATED_BODY()

public:
	ACardItemActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "", meta = (ClampMin = 0.0))
	float HealToHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (ClampMin = 0.0))
	float DamageToActor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "", meta = (ClampMin = 0.0))
	float AddToArmor = 0;

	/* The Number of Items in an inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1))
	int32 NumberOf;

	/* The Maximum Number of Items to be held in an inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1))
	int32 MaxNumberOf;

protected:
	virtual void Use(class APlayground_511Character* Character) override; // Change to your specific character

private:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	bool TraceHitResult();
};
