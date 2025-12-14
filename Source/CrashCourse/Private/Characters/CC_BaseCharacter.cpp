// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CC_BaseCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{

    PrimaryActorTick.bCanEverTick = false;

    // Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}



void ACC_BaseCharacter::GiveStartupAbilities()
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

    for (const auto& Ability : StartupAbilities)
    {
        FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
        ASC->GiveAbility(AbilitySpec);
    }
}

void ACC_BaseCharacter::InitializeAttributes()
{
    checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set."));
    UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

    FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
    FGameplayEffectSpecHandle SpecHandle       = ASC->MakeOutgoingSpec(InitializeAttributesEffect, 1, EffectContext);
    ASC->BP_ApplyGameplayEffectSpecToSelf(SpecHandle);
}
