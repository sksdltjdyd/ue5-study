// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // FInputActionValue를 위해 추가
#include "SlashCharactor.generated.h"

class UInputMappingContext; // 입력 매핑 컨텍스트 클래스 선언
class UInputAction; // 입력 액션 클래스 선언
class USpringArmComponent; // 스프링 암 컴포넌트 클래스 선언
class UCameraComponent; // 카메라 컴포넌트 클래스 선언

UCLASS()
class UNREALSTUDY_API ASlashCharactor : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharactor();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// 입력 매핑 컨텍스트 선언
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* SlashMappingContext;

	// 입력 매핑 선언
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovementAction;

	// 회전 입력 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	// 점프 입력 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	void Movement(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void DoJump(const FInputActionValue& Value);

private:
	// 스프링 암 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom; // 스프링 암 컴포넌트 선언
	
	// 카메라 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera; // 카메라 컴포넌트 선언
};

