// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SuperCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AttributeSets/AttributeSetBase.h"
#include "DataAssets/SupermanDataAsset.h"
#include "SuperAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

#include "GameplayEffectExtension.h"

#include "AbilitySystemLog.h"

#include "SuperCharacterMovementComponent.h"

// Sets default values
ASuperCharacterBase::ASuperCharacterBase(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<USuperCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for default collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SuperCharacterMovementComponent = Cast<USuperCharacterMovementComponent>(GetCharacterMovement());

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	AbilitySystemComponent = CreateDefaultSubobject<USuperAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ASuperCharacterBase::OnHealthAttributeChanged);
}

#pragma region Boilerplate
// Called when the game starts or when spawned
void ASuperCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASuperCharacterBase::PostLoad()
{
	Super::PostLoad();

	if (IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	}
}

UAbilitySystemComponent* ASuperCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
#pragma endregion

#pragma region AbilitySystem
bool ASuperCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext)
{
	if (!Effect.Get()) return false;

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, InEffectContext);
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		return ActiveGEHandle.WasSuccessfullyApplied();
	}

	return false;
}


void ASuperCharacterBase::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// Here we can react to a change in the health attribute

	/*
	if (Data.NewValue <= 0 && Data.OldValue > 0)
	{
		AActor* OtherCharacter = nullptr;

		if (Data.GEModData)
		{
			const FGameplayEffectContextHandle& EffectContext = Data.GEModData->EffectSpec.GetEffectContext();
			OtherCharacter = Cast<AActor>(EffectContext.GetInstigator());
		}

		FGameplayEventData EventPayload;
		EventPayload.EventTag = ZeroHealthEventTag;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, ZeroHealthEventTag, EventPayload);
	}
	*/
}


void ASuperCharacterBase::OnMaxMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void ASuperCharacterBase::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (auto DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
		}
	}
}

void ASuperCharacterBase::ApplyStartupEffects()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto CharacterEffect : CharacterData.Effects)
		{
			ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
		}
	}
}

void ASuperCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	GiveAbilities();
	ApplyStartupEffects();
}

void ASuperCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ASuperCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveActiveEffectsWithTags(InAirTags);
	}
}
#pragma endregion

#pragma region CharacterData
FCharacterData ASuperCharacterBase::GetCharacterData() const
{
	return CharacterData;
}

void ASuperCharacterBase::SetCharacterData(const FCharacterData& InCharacterData)
{
	CharacterData = InCharacterData;

	InitFromCharacterData(CharacterData);
}

void ASuperCharacterBase::InitFromCharacterData(const FCharacterData& InCharacterData, bool bFromReplication)
{

}

void ASuperCharacterBase::OnRep_CharacterData()
{
	InitFromCharacterData(CharacterData, true);
}
#pragma endregion

void ASuperCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASuperCharacterBase, CharacterData);
}