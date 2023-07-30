// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/SuperCharacterBase.h"
#include "Characters/PlayableCharacterBase.h"
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

	/** MappingContext */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* MoveAction;

	/** Look Input Action */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* LookAction;

	/** Fly Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlyAction;

	/** Boost Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BoostAction;


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
	// Called when the game starts or when spawned
	virtual void BeginPlay();


	// UNIQUE INPUT FUNCTIONALITY

	/** Called for flight input */
	void OnFlyPressed(const FInputActionValue& Value);

	void OnBoostPressed(const FInputActionValue& Value);
	void OnBoostReleased(const FInputActionValue& Value);

	//void Move(const FInputActionValue& Value);
	//void Look(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

#pragma region Gameplay Events
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FlyEventTag;
#pragma endregion
};
