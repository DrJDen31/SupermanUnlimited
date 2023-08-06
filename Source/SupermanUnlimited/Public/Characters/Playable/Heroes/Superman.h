// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/SuperCharacterBase.h"
#include "Characters/Playable/PlayableCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "SupermanUnlimitedTypes.h"
#include "InputActionValue.h"
#include "Superman.generated.h"

class USuperAbilitySystemComponent;
class USuperAttributeSet;

class UGameplayAbility;
class UGameplayEffect;

class USuperCharacterMovementComponent;

UCLASS()
class SUPERMANUNLIMITED_API ASuperman : public APlayableCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASuperman(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	virtual void PawnClientRestart() override;

public:

	// UNIQUE CHANGES IF NEEDED

	virtual void OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data) override;

	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data) override;

protected:

	virtual void GiveAbilities() override;

	virtual void Landed(const FHitResult& Hit) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();


public: // temp fix to make this public, wait for better workflow
	// UNIQUE INPUT FUNCTIONALITY

	/** Called for flight input */
	void OnFlyPressed(const FInputActionValue& Value);

	void OnBoostPressed(const FInputActionValue& Value);
	void OnBoostReleased(const FInputActionValue& Value);

protected:

	FGameplayAbilitySpecHandle FlightHandle;

#pragma region Gameplay Events
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FlyEventTag;
#pragma endregion


};
