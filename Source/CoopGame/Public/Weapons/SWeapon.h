// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

/*_____________________FORWARD DECLARATIONS_________________________*/
class USkeletalMeshComponent;
class UDamageType;

UCLASS()
class COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ASWeapon();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USkeletalMeshComponent* GunMeshComp;

protected:

	float ViewRange = 10000.0f; // Initial value for character viewing range (equals 100 metres)

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	TSubclassOf<UDamageType> DamageType;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void Fire();

private:	
	
	float BaseDamage = 20.0f;
	
};