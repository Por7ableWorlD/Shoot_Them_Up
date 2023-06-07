// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	// Ref on the ABaseGeometryActor class (or on all of it inheritors)
		//for spawn it
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometrySpawnClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};

UCLASS()
class SHOOTTHEMUP_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ref on the ABaseGeometryActor class (or on all of it inheritors)
		//for spawn it
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	// Ref on the any engine class
	/*UPROPERTY(EditAnywhere)
	UClass* Class;*/

	// Ref on the any ABaseGeometryActor objects in the world
	/*UPROPERTY(EditAnywhere)
	ABaseGeometryActor* GeometryObject;*/

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

private:	

	// Spawn objects with default SpawnActor function
	void SpawnActors(const uint8& SpawnCount);

	// Spawn objects with SpawnActorDeferred function - call BeginPlay event with delay in the spawned actors
		// BeginPlay will be call with help FinishSpawning() function 
	void DeferredSpawnActors(const uint8& SpawnCount);

	// Spawn objects with SpawnActorDeferred function
		// and also allows to configure emerging actors
	void CustomizableDeferredSpawnActors();

};
