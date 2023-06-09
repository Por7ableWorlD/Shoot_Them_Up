// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	// Get the initial actor location on the BeginPlay for the next manipulation
	InitialLocation = GetActorLocation();

	// Call base metods for UE_LOG()
	//OutputBaseLogs();
	//OutputStatToLogs();

	// Call metod for print something to player's screen
	//PrintBaseInfoInGame();

	// Call metod for print transform info
	//PrintTransform();

	// Call metod for create new material instanse and set color for it
	SetColor(GeometryData.Color);

	// Create ChangeMaterialColorTimer and set base settings
	GetWorldTimerManager().SetTimer(ChangeMaterialColorTimer, this, 
		&ABaseGeometryActor::OnChangeMaterialColorTimerFired, GeometryData.TimerRate_ChangeMaterialColor, true);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGeometryActor::OutputBaseLogs()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Display, TEXT("Weapon number = %d"), WeaponNum);
	UE_LOG(LogBaseGeometry, Display, TEXT("Kills number = %i"), KillsNum);
	UE_LOG(LogBaseGeometry, Display, TEXT("Health = %f"), Health);
	UE_LOG(LogBaseGeometry, Display, TEXT("Health = %.2f"), Health);
	UE_LOG(LogBaseGeometry, Display, TEXT("isDead = %d"), isDead);
	UE_LOG(LogBaseGeometry, Display, TEXT("HasWeapon = %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::OutputStatToLogs()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	FString WeaponNumStr = "Weapons num = " + FString::FromInt(WeaponNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString isDeadStr = "Is Dead: " + FString(isDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == All Stat: == \n\t%s\n\t%s\n\t%s"),
		*WeaponNumStr, *HealthStr, *isDeadStr);

	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);
}

void ABaseGeometryActor::PrintBaseInfoInGame()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Name");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Stat", true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::PrintTransformInfo()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	// We can use anouther variant to get all components like above:
	/*
	FTransform Transform = GetActorTransform();
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	FVector Scale = GetActorScale3D();
	*/

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());

	UE_LOG(LogBaseGeometry, Display, TEXT(" \nTransform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Scale: %s"), *Scale.ToString());

	UE_LOG(LogBaseGeometry, Error, TEXT(" \nTransform: %s\n "), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		SinMovement();
		break;
	}
	case EMovementType::Static:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}

void ABaseGeometryActor::SinMovement()
{
	// GetWorld() return the world object, which has any actors
	if (GetWorld())
	{
		// Number of seconds since the start of the game
		float Time = GetWorld()->GetTimeSeconds();

		// Got new current actor location right mow
		FVector CurrentLocation = GetActorLocation();

		// Calculate new Z actor coordinate, using the formula:
			// z = z0 + amplitude * sin(freq * t)
		CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

		// Set new location to actor
		SetActorLocation(CurrentLocation);
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	// if the BaseMesh poiter is null -> exit from function
	if (!BaseMesh) return;

	// Create new MaterialInstance and set it to first (0 index) material for BaseMesh
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnChangeMaterialColorTimerFired()
{
	if (++GeometryData.CurrentCount_ChangeMaterialColor
		<= GeometryData.MaxCount_ChangeMaterialColor)
	{
		const FLinearColor NewRandomColor = FLinearColor::MakeRandomColor();

		SetColor(NewRandomColor);

		UE_LOG(LogBaseGeometry, Display, TEXT("CurrentCount: %d \nNew random color for BaseMesh: %s \nFor Actor: %s"),
			GeometryData.CurrentCount_ChangeMaterialColor, *NewRandomColor.ToString(), *GetName());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ChangeMaterialColorTimer);
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer for ChangeMaterialColor has been stopped!"));
	}

}

