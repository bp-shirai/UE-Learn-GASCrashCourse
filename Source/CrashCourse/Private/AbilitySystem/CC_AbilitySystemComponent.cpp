// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/CC_AbilitySystemComponent.h"

#include "AbilitySystem/Abilities/CC_GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTags/CCTags.h"
#include "Logging/LogVerbosity.h"
#include "UObject/Object.h"

UCC_AbilitySystemComponent::UCC_AbilitySystemComponent()
{
}

void UCC_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
    Super::OnGiveAbility(AbilitySpec);

    HandleAutoActivateAbility(AbilitySpec);
    
}

void UCC_AbilitySystemComponent::OnRep_ActivateAbilities()
{
    Super::OnRep_ActivateAbilities();

    FScopedAbilityListLock ActiveScopeLock(*this);
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        HandleAutoActivateAbility(AbilitySpec);
    }
}

void UCC_AbilitySystemComponent::HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec)
{
   
    if (!IsValid(AbilitySpec.Ability)) return;

    if (AbilitySpec.Ability->GetAssetTags().HasTagExact(TAG::Ability::ActivateOnGiven))
    {
        TryActivateAbility(AbilitySpec.Handle);
    }
 
}
