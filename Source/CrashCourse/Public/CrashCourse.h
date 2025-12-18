// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Define category "LogGame"
CRASHCOURSE_API DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);

// Define alias to easily keep track of custom channels in C++ (must match what is specified in Project Settings > Collision
namespace CollisionChannel
{
    static constexpr int Projectile = ECC_GameTraceChannel1;
    static constexpr int Interact   = ECC_GameTraceChannel2;
} // namespace CollisionChannel

// Perception System simple Team Numbers
namespace TeamID
{
    static constexpr int Bots    = 1;
    static constexpr int Players = 2;
} // namespace TeamID

namespace CollisionProfile
{
    static const FName Ragdoll          = FName(TEXT("Ragdoll"));
    static const FName CharacterMesh    = FName(TEXT("CharacterMesh"));
    static const FName CharacterCapsule = FName(TEXT("CharacterCapsule"));
    static const FName NoCollision      = FName(TEXT("NoCollision"));
    static const FName Projectile       = FName(TEXT("Projectile"));
    static const FName Powerup          = FName(TEXT("Powerup"));
    static const FName Weapon           = FName(TEXT("Weapon"));
    static const FName HitBox           = FName(TEXT("HitBox"));
} // namespace CollisionProfile

static void LogOnScreen(const UObject* WorldContext, const FString& Msg, FColor Color = FColor::White, float Duration = 5.0f)
{
    const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull);

    // Net Prefix is helpful during PIE
    FString FullMessage = World->IsNetMode(NM_Client) ? "[CLIENT] " : "[SERVER] " + Msg;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FullMessage);
    }

    UE_LOG(LogGame, Log, TEXT("%s"), *FullMessage);
}