// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GAFly.h"
#include "GameFramework/Character.h"
#include "Characters/SuperCharacterBase.h"
#include "Components/SuperCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

UGAFly::UGAFly()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}


bool UGAFly::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGAFly::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
	
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	Character->bUseControllerRotationPitch = true;
	Character->bUseControllerRotationYaw = true;
	Character->bUseControllerRotationRoll = true;


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Magenta,
			FString::Printf(TEXT("Flight activated"))
		);
	}
}

void UGAFly::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ASuperCharacterBase* Character = CastChecked<ASuperCharacterBase>(ActorInfo->AvatarActor.Get());

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Character->bUseControllerRotationPitch = false;
	Character->bUseControllerRotationYaw = false;
	Character->bUseControllerRotationRoll = false;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Orange,
			FString::Printf(TEXT("Ending Flight"))
		);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
