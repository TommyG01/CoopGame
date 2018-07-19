// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"



ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/// Input Binding Delegate Functions
void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}
void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}
void ASCharacter::BeginCrouch()
{
	Crouch();
}
void ASCharacter::EndCrouch()
{
	UnCrouch();
}
