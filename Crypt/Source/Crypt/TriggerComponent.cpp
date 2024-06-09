// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    UE_LOG(LogTemp, Display, TEXT("constructor log"));
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("Trigger component alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // UE_LOG(LogTemp, Display, TEXT("Trigger component is ticking"));

    if (Mover == nullptr)
    {
        return;
    }

    AActor *Actor = GetAcceptedActor();
    if (Actor != nullptr)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMoverActorComponent *NewMover)
{
    Mover = NewMover;
}

AActor *UTriggerComponent ::GetAcceptedActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);

    for (AActor *Actor : Actors)
    {
        // FString ActorName = Actor->GetActorNameOrLabel();
        // UE_LOG(LogTemp, Display, TEXT("overlapping actor is: %s"), *ActorName);

        bool HasAcceptableTag = Actor->ActorHasTag(AcceptedActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");

        if (HasAcceptableTag && !IsGrabbed)
        {
            // UE_LOG(LogTemp, Display, TEXT("Unlocking"));
            return Actor;
        }
    }

    return nullptr;
}