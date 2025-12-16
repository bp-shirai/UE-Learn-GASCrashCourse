// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/ActorPoolingSubsystem.h"

#include "Containers/AllowShrinking.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Logging/StructuredLog.h"
#include "Framework/ActorPoolingInterface.h"
#include "CrashCourse.h"

AActor* UActorPoolingSubsystem::SpawnActorPooled(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod SpawnHandling)
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = SpawnHandling;

    return AcquireFromPool(WorldContextObject, ActorClass, SpawnTransform, SpawnParams);
}

AActor* UActorPoolingSubsystem::AcquireFromPool(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, FActorSpawnParameters SpawnParams)
{
    if (IsPoolingEnable(WorldContextObject))
    {
        if (UActorPoolingSubsystem* PoolingSubsystem = Get(WorldContextObject))
        {
            return PoolingSubsystem->AcquireFromPool_Internal(ActorClass, SpawnTransform, SpawnParams);
        }
    }

    // Fallback to standard spawning when not enabled
    return WorldContextObject->GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform, SpawnParams);
}



AActor* UActorPoolingSubsystem::AcquireFromPool_Internal(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, FActorSpawnParameters SpawnParams)
{
    // Acquire Actor from Pool
    AActor* AcquiredActor = nullptr;

    FActorPool& ActorPool = AvailableActorPools.FindOrAdd(ActorClass);
    
    // Grab fist available
    if (ActorPool.FreeActors.IsValidIndex(0))
    {
        UE_LOGFMT(LogGame, Log, "Acquired Actor for {ActorClass} from pool", GetNameSafe(ActorClass));
        AcquiredActor = ActorPool.FreeActors[0];

        // Remove from pool
        // @todo: keep in pool but mark as in-use
        ActorPool.FreeActors.RemoveAtSwap(0, 1, EAllowShrinking::No);
    }

    // Failed to find actor
    if (!AcquiredActor)
    {
        UE_LOGFMT(LogGame, Log, "Actor Pool empty, spawning new Actor for {ActorClass}", GetNameSafe(ActorClass));

        // Spawn fresh instance that can eventually be release to the pool
        return GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform, SpawnParams);
    }

    AcquiredActor->SetActorTransform(SpawnTransform);
    AcquiredActor->SetInstigator(SpawnParams.Instigator);
    AcquiredActor->SetOwner(SpawnParams.Owner);

    // There are assumed not used by game code
    AcquiredActor->SetActorEnableCollision(true);
    AcquiredActor->SetActorHiddenInGame(false);

    AcquiredActor->DispatchBeginPlay();

    IActorPoolingInterface::Execute_PoolBeginPlay(AcquiredActor);

    return AcquiredActor;
}


bool UActorPoolingSubsystem::ReleaseToPool(AActor* Actor)
{
    if (IsPoolingEnable(Actor))
    {
        if (UActorPoolingSubsystem* PoolingSubsystem = Get(Actor))
        {
            return PoolingSubsystem->ReleaseToPool_Internal(Actor);
        }
    }

    // Destroy Actor No Pool
    Actor->Destroy();

    return false;
}

bool UActorPoolingSubsystem::ReleaseToPool_Internal(AActor* Actor)
{
    // Release Actor to Pool
    check(IsValid(Actor));

    // There are assumed not used by game code
    Actor->SetActorEnableCollision(false);
    Actor->SetActorHiddenInGame(true);

    Actor->RouteEndPlay(EEndPlayReason::Destroyed);

    IActorPoolingInterface::Execute_PoolEndPlay(Actor);

    // Place in the pool for later use
    FActorPool& ActorPool = AvailableActorPools.FindOrAdd(Actor->GetClass());
    ActorPool.FreeActors.Add(Actor);

    return true;
}


void UActorPoolingSubsystem::PrimeActorPool(TSubclassOf<AActor> ActorClass, int32 PoolSize)
{
    UE_LOGFMT(LogGame, Log, "Priming Pool for {ActorClass} (Amount)", GetNameSafe(ActorClass), PoolSize);

    // Prime a set number of pooled actors, this reduse memory fragmentation and any potential initial hitches during gameplay
    for (int i = 0; i < PoolSize; i++)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        // @fixme: this can trigger an overlap when spawned, for example in empty level it may overlap SpectatorPawn in world zero
        // ideally we can prevent the projectile from fully activating to avoid this overlap
        AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorClass, FTransform::Identity, SpawnParams);

        ReleaseToPool(NewActor);
    }
}


bool UActorPoolingSubsystem::IsPoolingEnable(const UObject* WorldContextObject)
{
    return true;
}

UActorPoolingSubsystem* UActorPoolingSubsystem::Get(const UObject* WorldContextObject)
{
    const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
    return World ? World->GetSubsystem<UActorPoolingSubsystem>() : nullptr;
}
