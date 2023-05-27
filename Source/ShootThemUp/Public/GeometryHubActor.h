// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ref on the ABaseGeometryActor class for spawn it
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	// Ref on the any engine class
	UPROPERTY(EditAnywhere)
	UClass* Class;

	// Ref on the any ABaseGeometryActor objects in the world
	UPROPERTY(EditAnywhere)
	ABaseGeometryActor* GeometryObject;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
