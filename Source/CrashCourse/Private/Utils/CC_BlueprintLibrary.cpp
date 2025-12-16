// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/CC_BlueprintLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Logging/LogVerbosity.h"
#include "Serialization/MemoryLayout.h"
#include "Utils/CC_GameTypes.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
    const float Dot = FVector::DotProduct(TargetForward, ToInstigator);

    if (Dot < -0.5f)
    {
        return EHitDirection::Back;
    }
    else if (Dot < 0.5f)
    {
        // Either Left or Right
        const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
        if (Cross.Z < 0.f)
        {
            return EHitDirection::Left;
        }
        else
        {
            return EHitDirection::Right;
        }
    }

    return EHitDirection::Forward;
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
    switch (HitDirection)
    {
        case EHitDirection::Left: return FName("Left");
        case EHitDirection::Right: return FName("Right");
        case EHitDirection::Forward: return FName("Forward");
        case EHitDirection::Back: return FName("Back");
        default: return FName("None");
    }
}

bool UCC_BlueprintLibrary::ApplyGameplayTagInNone(UAbilitySystemComponent* TargetASC, const FGameplayTag& Tag)
{
    if (TargetASC->HasMatchingGameplayTag(Tag))
    {
        return false;
    }
    else
    {
        TargetASC->AddLooseGameplayTag(Tag);
        return true;
    }
}

bool UCC_BlueprintLibrary::RemoveGameplayTagInFound(UAbilitySystemComponent* TargetASC, const FGameplayTag& Tag)
{
    if (TargetASC->HasMatchingGameplayTag(Tag))
    {
        TargetASC->RemoveLooseGameplayTag(Tag);
        return true;
    }
    else
    {
        return false;
    }
}

void UCC_BlueprintLibrary::SetRagdollEnable(bool bEnable, ACharacter* Character)
{
    if (!Character) return;
    USkeletalMeshComponent* MeshComponent = Character->GetMesh();
    UCapsuleComponent* CapsuleComponent   = Character->GetCapsuleComponent();
    if (!MeshComponent || !CapsuleComponent) return;

    if (bEnable)
    {
        MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
        MeshComponent->SetSimulatePhysics(true);
    }
    else
    {
        Character->GetClass()->GetDefaultObject<ACharacter>()->GetMovementComponent()->StopMovementImmediately();

        MeshComponent->SetSimulatePhysics(false);
        MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        MeshComponent->AttachToComponent(CapsuleComponent, FAttachmentTransformRules::KeepRelativeTransform);
        if (const ACharacter* CDO = Character->GetClass()->GetDefaultObject<ACharacter>())
        {
            const FTransform MeshRelativeTransform = CDO->GetMesh()->GetRelativeTransform();
            MeshComponent->SetRelativeTransform(MeshRelativeTransform);
            
        }
    }
}
