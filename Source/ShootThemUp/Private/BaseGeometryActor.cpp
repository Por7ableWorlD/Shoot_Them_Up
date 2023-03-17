// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Вызываем базовые методы по работе с UE_LOG()
	//OutputBaseLogs();
	//OutputStatToLogs();

	// Вызываем метод для вывода чего-либо на экран игрока в игре
	//PrintBaseInfoInGame();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::OutputBaseLogs()
{
	UE_LOG(LogTemp, Display, TEXT("Weapon number = %d"), WeaponNum);
	UE_LOG(LogTemp, Display, TEXT("Kills number = %i"), KillsNum);
	UE_LOG(LogTemp, Display, TEXT("Health = %f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Health = %.2f"), Health);
	UE_LOG(LogTemp, Display, TEXT("isDead = %d"), isDead);
	UE_LOG(LogTemp, Display, TEXT("HasWeapon = %d"), static_cast<int>(HasWeapon));
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
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Name");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Stat", true, FVector2D(1.5f, 1.5f));
}

