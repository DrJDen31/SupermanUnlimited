// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/SuperCharacterBase.h"
#include "SuperCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANUNLIMITED_API USuperCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	ASuperCharacterBase* SuperCharacterOwner;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Boosted_MaxFlySpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hover_MaxFlySpeed;

	bool IsBoosting = false;
	
protected:

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	float MovingForwardAmount() const;
	float MovingForwardAmountFlying() const;

	virtual void InitializeComponent() override;
};
