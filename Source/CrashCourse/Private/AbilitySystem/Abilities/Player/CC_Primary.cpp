// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/Player/CC_Primary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

#include "GameplayTags/CCTags.h"

UCC_Primary::UCC_Primary()
{
}

TArray<AActor*> UCC_Primary::HitBoxOverlapTest()
{
    AActor* AvatarActor = GetAvatarActorFromActorInfo();

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(AvatarActor);

    // Ensure that the overlap test ignores the Avatar Actor
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActors(ActorsToIgnore);

    FCollisionResponseParams ResponseParams;
    ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
    ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

    TArray<FOverlapResult> OverlapResults;
    FCollisionShape Shape = FCollisionShape::MakeSphere(HitBoxRadius);

    const FVector Forward        = AvatarActor->GetActorForwardVector() * HitBoxForwardOffset;
    const FVector HitBoxLocation = AvatarActor->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);

    GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Shape, QueryParams, ResponseParams);

    TArray<AActor*> ActorsHit;
    for (const FOverlapResult& Result : OverlapResults)
    {
        AActor* HitActor = Result.GetActor();
        if (IsValid(HitActor))
        {
            ActorsHit.AddUnique(HitActor);
        }
    }

    if (bDrawDebug)
    {
        DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
    }

    return ActorsHit;
}

void UCC_Primary::SendHitReactEventToActors(const TArray<AActor*>& ActorsHit)
{
    for (AActor* HitActor : ActorsHit)
    {
        FGameplayEventData EventData;
        EventData.Instigator = GetAvatarActorFromActorInfo();
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, TAG::Event::Enemy::HitReact, EventData);
    }
}

void UCC_Primary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{

    DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);

    for (const FOverlapResult& Result : OverlapResults)
    {
        if (IsValid(Result.GetActor()))
        {
            FVector Location  = Result.GetActor()->GetActorLocation();
            FVector BoxExtent = Result.GetActor()->GetComponentsBoundingBox().GetExtent();

            DrawDebugBox(GetWorld(), Location, BoxExtent, FColor::Green, false, 3.f);
        }
    }
}
