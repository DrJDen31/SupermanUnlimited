// Copyright Jaden Tompkins


#include "Player/Controllers/SUPlayerController.h"

#include "Characters/Playable/PlayableCharacterBase.h"
#include "Components/SuperCharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "InputActionValue.h"


ASUPlayerController::ASUPlayerController()
{
	bReplicates = true;
}

void ASUPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
}

void ASUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASUPlayerController::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASUPlayerController::Look);
	}
}

void ASUPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	APlayableCharacterBase* ControlledCharacter = GetPawn<APlayableCharacterBase>();

	if (!ControlledCharacter)
	{
		return;
	}

	if (ControlledCharacter->GetCharacterMovement()->IsFlying())
	{
		const FRotator Rotation = GetControlRotation();
		const FVector Direction = Rotation.Vector();
		ControlledCharacter->AddMovementInput(Direction, MovementVector.Y);

		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
	}
	else
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FRotator PitchRotation(Rotation.Pitch, 0, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASUPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}