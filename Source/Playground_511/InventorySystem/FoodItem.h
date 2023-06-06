// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_511_API UFoodItem : public UItems
{
	GENERATED_BODY()

public:
    /**Health to heal character*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
    float HealthToHeal = 20.f;

protected:
	virtual void Use(class APlayground_511Character* Character) override;
};
