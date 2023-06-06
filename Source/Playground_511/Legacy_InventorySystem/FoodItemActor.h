// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "FoodItemActor.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_511_API AFoodItemActor : public AItemActor
{
	GENERATED_BODY()

public:
    /**Health to heal character*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        float HealthToHeal;

protected:

    virtual void Use(class APlayground_511Character* Character) override;
};
