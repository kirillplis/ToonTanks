// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()


public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

	bool bAlive = true;

private:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	// class USpringArmComponent* SpringArm;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	// class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnRate = 5.f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed = 5.f;

	APlayerController* TankPlayerController;
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* TankMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	// class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* FireAction;

	void Move(const FInputActionValue& Value);
	// void Aim(const FInputActionValue& Value);
	// void Fire(const FInputActionValue& Value);
};

