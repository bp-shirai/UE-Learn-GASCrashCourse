#pragma once

#include "CoreMinimal.h"

#include "CC_GameTypes.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
    Left,
    Right,
    Forward,
    Back,
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(BlueprintReadWrite)
    float Distance{0.f};
};