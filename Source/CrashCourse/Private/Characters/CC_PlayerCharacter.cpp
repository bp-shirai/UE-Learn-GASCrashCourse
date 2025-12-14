// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CC_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"

#include "AbilitySystem/CC_AttributeSet.h"
#include "Player/CC_PlayerState.h"
#include "UObject/Object.h"

ACC_PlayerCharacter::ACC_PlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw   = false;
    bUseControllerRotationRoll  = false;

    GetCharacterMovement()->bOrientRotationToMovement  = true;
    GetCharacterMovement()->RotationRate               = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity              = 500.f;
    GetCharacterMovement()->AirControl                 = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed               = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed         = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength         = 600.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* ACC_PlayerCharacter::GetAbilitySystemComponent() const
{
    const ACC_PlayerState* CCPlayerState = GetPlayerState<ACC_PlayerState>();
    return IsValid(CCPlayerState) ? CCPlayerState->GetAbilitySystemComponent() : nullptr;
}

UAttributeSet* ACC_PlayerCharacter::GetAttributeSet() const
{
    const ACC_PlayerState* CCPlayerState = GetPlayerState<ACC_PlayerState>();
    return IsValid(CCPlayerState) ? CCPlayerState->GetAttributeSet() : nullptr;
}

void ACC_PlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (HasAuthority())
    {
        UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
        if (IsValid(ASC))
        {
            ASC->InitAbilityActorInfo(GetPlayerState(), this);
            GiveStartupAbilities();
            InitializeAttributes();

            OnAbilitySystemInitialized.Broadcast(ASC, GetAttributeSet());
        }
    }
}

void ACC_PlayerCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
    if (IsValid(ASC))
    {
        ASC->InitAbilityActorInfo(GetPlayerState(), this);

        ASC->GetGameplayAttributeValueChangeDelegate(UCC_AttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);

        OnAbilitySystemInitialized.Broadcast(ASC, GetAttributeSet());
    }
}
