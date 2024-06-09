// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverActorComponent.h"
#include "TriggerComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPT_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// constructor
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMoverActorComponent *Mover);

private:
	UPROPERTY(EditAnywhere)
	FName AcceptedActorTag;

	UMoverActorComponent *Mover;

	AActor *GetAcceptedActor() const;
};
