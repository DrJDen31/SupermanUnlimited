// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "SupermanUnlimitedTypes.h"
#include "SuperCharacterBase.generated.h"

class USuperAbilitySystemComponent;
class UAttributeSetBase;

class UGameplayAbility;
class UGameplayEffect;

class USuperCharacterMovementComponent;

UCLASS()
class SUPERMANUNLIMITED_API ASuperCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASuperCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditDefaultsOnly)
	USuperAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(Transient)
	UAttributeSetBase* AttributeSet;

	USuperCharacterMovementComponent* SuperCharacterMovementComponent;

public:

	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& InCharacterData);

	virtual void OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data);

	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

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

protected:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InAirTags;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
