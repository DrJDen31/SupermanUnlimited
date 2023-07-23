// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
class SUPERMANUNLIMITED_API ASuperman : public ACharacter, public IAbilitySystemInterface
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
	class UInputAction* FlyAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	ASuperman(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);

	virtual void PawnClientRestart() override;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditDefaultsOnly)
	USuperAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(Transient)
	USuperAttributeSet* AttributeSet;

	USuperCharacterMovementComponent* SuperCharacterMovementComponent;

public:

	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& InCharacterData);

	void OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data);

	//void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

protected:

	UPROPERTY(ReplicatedUsing = OnRep_CharacterData)
	FCharacterData CharacterData;

	UFUNCTION()
	void OnRep_CharacterData();

	virtual void InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication = false);

	UPROPERTY(EditDefaultsOnly)
	class USupermanDataAsset* CharacterDataAsset;

protected:

	void GiveAbilities();
	void ApplyStartupEffects();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	FDelegateHandle MaxMovementSpeedChangedDelegateHandle;

protected:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FlyEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttackStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttackEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FocusStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag FocusEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag WeakenedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ZeroHealthEventTag;

	// Gameplay Tags

protected:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InAirTags;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for flight input */
	void OnFlyPressed(const FInputActionValue& Value);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
