// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SuperCharacterMovementComponent.h"



void USuperCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Flying)
	{
		// Could consider updating WantsToSprint to make the user "re-sprint" after 
		// walking sideways or backwards.

		if (IsBoosting && MovingForwardAmountFlying() > 0.85)
		{
			MaxFlySpeed = Boosted_MaxFlySpeed;
		}
		else if (IsBoosting && MovingForwardAmountFlying() > 0.7)
		{
			MaxFlySpeed = (Boosted_MaxFlySpeed + Hover_MaxFlySpeed) / 2;
		}
		else
		{
			MaxFlySpeed = Hover_MaxFlySpeed;
		}
	}
}

float USuperCharacterMovementComponent::MovingForwardAmountFlying() const
{
	if (!SuperCharacterOwner)
	{
		return 0.f;
	}

	FVector Forward = PawnOwner->GetActorForwardVector();
	FVector MoveDirection = Velocity.GetSafeNormal();

	float VelocityDot = FVector::DotProduct(Forward, MoveDirection);
	return VelocityDot;
}

float USuperCharacterMovementComponent::MovingForwardAmount() const
{
	if (!SuperCharacterOwner)
	{
		return 0.f;
	}

	FVector Forward = PawnOwner->GetActorForwardVector();
	FVector MoveDirection = Velocity.GetSafeNormal();

	//Ignore vertical movement
	Forward.Z = 0.0f;
	MoveDirection.Z = 0.0f;

	float VelocityDot = FVector::DotProduct(Forward, MoveDirection);
	return VelocityDot;
}

void USuperCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SuperCharacterOwner = Cast<ASuperCharacterBase>(GetOwner());
}