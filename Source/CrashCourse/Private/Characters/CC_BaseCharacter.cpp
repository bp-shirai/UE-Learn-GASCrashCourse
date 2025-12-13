// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CC_BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{

    PrimaryActorTick.bCanEverTick = false;

    // Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
    return nullptr;
}

void ACC_BaseCharacter::GiveStartupAbilities()
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
    if (!IsValid(ASC)) return;

    for (const auto& Ability : StartupAbilities)
    {
        FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
        ASC->GiveAbility(AbilitySpec);
    }
}
