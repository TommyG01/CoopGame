// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	GunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("GunMeshComp"));
	RootComponent = GunMeshComp;
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASWeapon::Fire()
{
	// Trace the world from pawn eyes to crosshair location
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation; // Out Parameter
		FRotator  EyeRotation;  // Out Parameter
		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * ViewRange);
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		FHitResult Hit;  // Out Parameter

		if (GetWorld()->LineTraceSingleByChannel
				(
					Hit,						// struct FHitResult & OutHit
					EyeLocation,		// const FVector & Start
					TraceEnd,			// const FVector & End
					ECC_Visibility,	// ECollisionChannel TraceChannel
					QueryParams	// const FCollisionQueryParams & Params
												// const FCollisionResponseParams & ResponseParam (Default)
				)
			)
		{
			// Is a blocking Hit : Process Damage
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);
		}
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);  // ToDo: Temp Debug Logging
	}
}

void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}