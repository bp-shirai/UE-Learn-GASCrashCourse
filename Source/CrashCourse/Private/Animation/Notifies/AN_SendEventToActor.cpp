// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/Notifies/AN_SendEventToActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameplayTagContainer.h"

UAN_SendEventToActor::UAN_SendEventToActor()
{
    bIsNativeBranchingPoint = true;
}

void UAN_SendEventToActor::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
    Super::BranchingPointNotify(BranchingPointPayload);

    const USkeletalMeshComponent* MeshComp = BranchingPointPayload.SkelMeshComponent;

    AActor* OwnerActor = MeshComp ? MeshComp->GetOwner() : nullptr;
    if (OwnerActor && OwnerActor->Implements<UAbilitySystemInterface>())
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, FGameplayEventData());
    }
}

FString UAN_SendEventToActor::GetNotifyName_Implementation() const
{
    if (EventTag.IsValid())
    {
        return EventTag.GetTagLeafName().ToString();
    }

    return TEXT("None");
}
