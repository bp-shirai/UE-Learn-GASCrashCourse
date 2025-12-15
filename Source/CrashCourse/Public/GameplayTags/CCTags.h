#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace TAG
{
    namespace Ability
    {
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);

        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
    } // namespace Ability

    namespace Event
    {
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored);

        namespace Enemy
        {
            UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
        }
    } // namespace Event

    namespace Status
    {
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead);
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stunned);
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(Invulnerable);
    } // namespace Status
} // namespace TAG