// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CC_PlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "GameplayTags/CCTags.h"
#include "Logging/StructuredLog.h"

#include "GameplayTags/CCTags.h"

void ACC_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        for (UInputMappingContext* Context : InputMappingContexts)
        {
            Subsystem->AddMappingContext(Context, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComp->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);
        EnhancedInputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
        EnhancedInputComp->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
        EnhancedInputComp->BindAction(IA_Primary, ETriggerEvent::Triggered, this, &ThisClass::Primary);
        EnhancedInputComp->BindAction(IA_Secondary, ETriggerEvent::Triggered, this, &ThisClass::Secondary);
        EnhancedInputComp->BindAction(IA_Tertiary, ETriggerEvent::Triggered, this, &ThisClass::Tertiary);
    }
}

void ACC_PlayerController::Jump(const FInputActionValue& Value)
{
    if (!IsValid(GetCharacter())) return;

    const bool bPressed = Value.Get<bool>();
    if (bPressed)
    {
        GetCharacter()->Jump();
    }
    else
    {
        GetCharacter()->StopJumping();
    }
}

void ACC_PlayerController::Move(const FInputActionValue& Value)
{
    if (!IsValid(GetPawn())) return;

    const FVector2D Input   = Value.Get<FVector2D>().GetSafeNormal();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    const FVector Movement = ForwardDirection * Input.Y + RightDirection * Input.X;

    GetPawn()->AddMovementInput(Movement);
}

void ACC_PlayerController::Look(const FInputActionValue& Value)
{
    if (!IsValid(GetPawn())) return;

    const FVector2D Input = Value.Get<FVector2D>();

    AddYawInput(Input.X);
    AddPitchInput(Input.Y);
}


void ACC_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag)
{
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
    if (!IsValid(ASC)) return;
    
    ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

void ACC_PlayerController::Primary(const FInputActionValue& Value)
{
    ActivateAbility(TAG::Ability::Primary);
}

void ACC_PlayerController::Secondary(const FInputActionValue& Value)
{
    ActivateAbility(TAG::Ability::Secondary);
}

void ACC_PlayerController::Tertiary(const FInputActionValue& Value)
{
    ActivateAbility(TAG::Ability::Tertiary);
}
