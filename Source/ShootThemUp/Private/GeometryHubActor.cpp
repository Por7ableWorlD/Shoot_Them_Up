// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	//SpawnActors(4);
	//DeferredSpawnActors(8);

	CustomizableDeferredSpawnActors();
}

void AGeometryHubActor::SpawnActors(const uint8& SpawnCount)
{
	// Just a world pointer
	UWorld* World = GetWorld();
	
	if (World)
	{
		for (uint8 i = 0; i < SpawnCount; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
			ABaseGeometryActor* GeometryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (GeometryActor)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				GeometryActor->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DeferredSpawnActors(const uint8& SpawnCount)
{
	// Just a world pointer
	UWorld* World = GetWorld();

	if (World)
	{
		for (uint8 i = 0; i < SpawnCount; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (GeometryActor)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Data.Color = FLinearColor::MakeRandomColor();
				GeometryActor->SetGeometryData(Data);
				GeometryActor->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::CustomizableDeferredSpawnActors()
{
	// Just a world pointer
	UWorld* World = GetWorld();

	if (World)
	{
		// Range version of For Loop
		for (FGeometryPayload Payload : GeometryPayloads)
		{
			ABaseGeometryActor* SpawnActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometrySpawnClass, Payload.InitialTransform);

			if (SpawnActor)
			{
				SpawnActor->SetGeometryData(Payload.Data);
				SpawnActor->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

