// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_SendEventToActor.generated.h"

/**
 *
 */
UCLASS()
class CRASHCOURSE_API UAN_SendEventToActor : public UAnimNotify
{
    GENERATED_BODY()

public:
    UAN_SendEventToActor();
    virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
    virtual FString GetNotifyName_Implementation() const override;

    UPROPERTY(EditAnywhere, Category = GameplayTags)
    FGameplayTag EventTag;
};
