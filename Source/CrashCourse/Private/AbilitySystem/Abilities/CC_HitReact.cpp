// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(const AActor* Instigator)
{
    const AActor* AvatarActor = GetAvatarActorFromActorInfo();
    if (!IsValid(AvatarActor) || !IsValid(Instigator)) return;

    AvatarForward = AvatarActor->GetActorForwardVector();

    const FVector AvatarLocation     = AvatarActor->GetActorLocation();
    const FVector InstigatorLocation = Instigator->GetActorLocation();

    ToInstigator = InstigatorLocation - AvatarLocation;
    ToInstigator.Normalize();
}
