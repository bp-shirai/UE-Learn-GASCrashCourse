// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/CC_GameplayAbility.h"

#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "Characters/CC_BaseCharacter.h"
#include "Characters/CC_EnemyCharacter.h"

void UCC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (bDrawDebug && IsValid(GEngine))
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("%s Activated"), *GetName()));
    }
}

UCC_AbilitySystemComponent* UCC_GameplayAbility::GetCCAbilitySystemComponent() const
{
    return Cast<UCC_AbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}

ACC_BaseCharacter* UCC_GameplayAbility::GetCCBaseCharacter() const
{
    return Cast<ACC_BaseCharacter>(GetAvatarActorFromActorInfo());
}

ACC_EnemyCharacter* UCC_GameplayAbility::GetCCEnemyCharacter() const
{
    return Cast<ACC_EnemyCharacter>(GetAvatarActorFromActorInfo());
}
