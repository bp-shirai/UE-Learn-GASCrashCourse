// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/CC_BaseCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Engine/EngineTypes.h"
#include "GameplayAbilitySpec.h"
#include "GameplayEffectTypes.h"
#include "Logging/LogVerbosity.h"

#include "AbilitySystem/CC_AttributeSet.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{

    PrimaryActorTick.bCanEverTick = false;

    // Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACC_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, bAlive, COND_None, REPNOTIFY_Always);
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

    ASC->GetGameplayAttributeValueChangeDelegate(UCC_AttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void ACC_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    if (Data.NewValue <= 0.f)
    {
        HandleDeath();
    }
}

void ACC_BaseCharacter::HandleDeath()
{
    SetAlive(false);

    UE_LOG(LogTemp, Warning, TEXT("ACC_BaseCharacter::HandleDeath : %s"), *GetName());
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACC_BaseCharacter::HandleRespawn()
{
    SetAlive(true);

    UE_LOG(LogTemp, Warning, TEXT("ACC_BaseCharacter::HandleRespawn : %s"), *GetName());
}

