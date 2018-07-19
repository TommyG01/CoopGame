// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

/*_____________________FORWARD DECLARATIONS_________________________*/
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent * CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;


	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginCrouch();
	void EndCrouch();

private:	
	
};
