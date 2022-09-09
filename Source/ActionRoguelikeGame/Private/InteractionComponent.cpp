// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "SGameplayInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner=GetOwner();

	FVector EyeLocation;
	FRotator EyeRotaton;

	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotaton);

	FVector End=EyeLocation+(EyeRotaton.Vector()*1000.0f);
	
	FHitResult Hit;

	
	GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);
	AActor* HitActor=Hit.GetActor();

	if(HitActor)
	{
		if(HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyPawn=Cast<APawn>(MyOwner);
			ISGameplayInterface::Execute_Interact(HitActor,MyPawn);
		}
	}
	DrawDebugLine(GetWorld(),EyeLocation,End,FColor::Red,false,2.0f,0,2.0f);
}

