// Fill out your copyright notice in the Description page of Project Settings.


#include "Superman.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SuperAttributeSet.h"
#include "DataAssets/SupermanDataAsset.h"
#include "SuperAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

#include "SuperCharacterMovementComponent.h"

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
	/*
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	*/
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

// Called to bind functionality to input
void ASuperman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Flight
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &ASuperman::OnFlyPressed);

		//Boost
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Triggered, this, &ASuperman::OnBoostPressed);
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Completed, this, &ASuperman::OnBoostReleased);

		//Moving
	    //EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASuperman::Move);

		//Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASuperman::Look);

	}
}

/*
void ASuperman::Move(const FInputActionValue& Value)
{

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASuperman::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
*/

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

	/*
	if (SuperCharacterMovementComponent->IsFlying()) 
	{
		SuperCharacterMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}
	else
	{
		SuperCharacterMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
		bUseControllerRotationPitch = true;
		bUseControllerRotationYaw = true;
		bUseControllerRotationRoll = true;
	}

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Blue,
			FString::Printf(TEXT("FlyPressed"))
		);
	}
	*/
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