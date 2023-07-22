// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ATank::ATank()
{
  // PrimaryActorTick.bCanEverTick = true;

  // SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  // SpringArm->SetupAttachment(RootComponent);

  // Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  // Camera->SetupAttachment(SpringArm);
}

void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		// EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ATank::Aim);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
	}
}


void ATank::BeginPlay()
{
	Super::BeginPlay();

  if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
  { 
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
				Subsystem->AddMappingContext(TankMappingContext, 0);
		}
  }

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(const FInputActionValue &Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	// const FRotator Rotation = Controller->GetControlRotation();
	// const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// AddMovementInput(ForwardDirection, MovementVector.Y);
	// const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// AddMovementInput(RightDirection, MovementVector.X);

	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.Y * Speed / 10);

	const FRotator Turn = FRotator(0.f, MovementVector.X * TurnRate, 0.f);
	AddActorWorldRotation(Turn, true);	

	// AddControllerYawInput(MovementVector.X * TurnRate / 2);
	// AddControllerPitchInput(MovementVector.Y);
}

// void ATank::Aim(const FInputActionValue& Value)
// {
// 	FVector2D AimAxisVector = Value.Get<FVector2D>();
// 	if (Controller)
// 	{
// 		AddControllerYawInput(AimAxisVector.X);
// 		AddControllerPitchInput(AimAxisVector.Y);
// 	}
// }

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}