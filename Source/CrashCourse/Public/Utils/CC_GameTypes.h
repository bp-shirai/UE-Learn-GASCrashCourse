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