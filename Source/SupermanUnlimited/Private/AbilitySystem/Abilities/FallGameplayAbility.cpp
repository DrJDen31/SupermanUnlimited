// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/FallGameplayAbility.h"
#include "GameFramework/Character.h"
#include "Characters/SuperCharacterBase.h"
#include "SuperCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

UFallGameplayAbility::UFallGameplayAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}


bool UFallGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UFallGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Magenta,
			FString::Printf(TEXT("Attempting to activate flight"))
		);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ASuperCharacterBase* Character = CastChecked<ASuperCharacterBase>(ActorInfo->AvatarActor.Get());

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Character->bUseControllerRotationPitch = false;
	Character->bUseControllerRotationYaw = false;
	Character->bUseControllerRotationRoll = false;


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Magenta,
			FString::Printf(TEXT("Falling"))
		);
	}
}

void UFallGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

