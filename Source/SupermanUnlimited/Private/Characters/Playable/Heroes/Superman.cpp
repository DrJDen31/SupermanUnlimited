// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Playable/Heroes/Superman.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AttributeSets/SuperAttributeSet.h"
#include "DataAssets/SupermanDataAsset.h"
#include "AbilitySystem/SuperAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

#include "Components/SuperCharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "InputActionValue.h"

#include "GameplayEffectExtension.h"

#include "AbilitySystemLog.h"


// Sets default values
ASuperman::ASuperman(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Override size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	// UNIQUE ATTRIBUTE SET

	AttributeSet = CreateDefaultSubobject<USuperAttributeSet>(TEXT("AttributeSet"));


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxMovementSpeedAttribute()).AddUObject(this, &ASuperman::OnMaxMovementSpeedChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ASuperman::OnHealthAttributeChanged);
}

#pragma region Boilerplate
// Called when the game starts or when spawned
void ASuperman::BeginPlay()
{
	Super::BeginPlay();
}

void ASuperman::PostLoad()
{
	Super::PostLoad();

}

void ASuperman::PawnClientRestart()
{
	Super::PawnClientRestart();

	/*
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	*/
}
#pragma endregion

#pragma region AbilitySystem

void ASuperman::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// Here we can override the base reaction if needed
}

void ASuperman::OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	// Here we can override the base reaction if needed
}

void ASuperman::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		USupermanDataAsset* SDA = Cast<USupermanDataAsset>(SuperCharacterDataAsset);
		FlightHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(SDA->FlyAbility));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Cyan,
				FString::Printf(TEXT("Granting Ability"))
			);
		}
	}
}
#pragma endregion

void ASuperman::OnFlyPressed(const FInputActionValue& Value) 
{
	if (SuperCharacterMovementComponent->IsFlying())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Magenta,
				FString::Printf(TEXT("Attempting to Fall"))
			);
		}
		
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
			AbilitySystemComponent->CancelAbilityHandle(FlightHandle);
		}

	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Magenta,
				FString::Printf(TEXT("Attempting Flight"))
			);
		}

		FGameplayEventData Payload;
		Payload.Instigator = this;
		Payload.EventTag = FlyEventTag;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, FlyEventTag, Payload);
	}
}

void ASuperman::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAbilityHandle(FlightHandle);
	}
}

void ASuperman::OnBoostPressed(const FInputActionValue& Value)
{
	SuperCharacterMovementComponent->IsBoosting = true;
}

void ASuperman::OnBoostReleased(const FInputActionValue& Value)
{
	SuperCharacterMovementComponent->IsBoosting = false;
}