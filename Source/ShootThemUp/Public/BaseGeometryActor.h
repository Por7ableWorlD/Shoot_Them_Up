// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	// How much the actor will deviate from a initial point
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 50.0f;
	
	// Oscillation frequency
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate_ChangeMaterialColor = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Design")
	int32 MaxCount_ChangeMaterialColor = 5;

	int32 CurrentCount_ChangeMaterialColor = 0;
};

UCLASS()
class SHOOTTHEMUP_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ABaseGeometryActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponNum = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 54.2351f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool isDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

	UPROPERTY(EditAnywhere, Category = "Geometry Data")
	FGeometryData GeometryData;

private:

	FVector InitialLocation;

	FTimerHandle ChangeMaterialColorTimer;

	// Base metods for UE_LOG()
	void OutputBaseLogs();
	void OutputStatToLogs();
	// and print something to palyer's screen
	void PrintBaseInfoInGame();

	// Base metod for print transform metods
	void PrintTransformInfo();

	// Set actor stop/movement
	void HandleMovement();
	// Make actor Sin movement
	void SinMovement();

	// Set color to BaseMesh
	void SetColor(const FLinearColor& Color);

	void OnChangeMaterialColorTimerFired();
};
