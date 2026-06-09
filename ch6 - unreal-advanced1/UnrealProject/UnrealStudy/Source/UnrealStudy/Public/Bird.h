// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h" // FInputActionValue를 위해 추가
#include "Bird.generated.h"

class UCapsuleComponent; // 캡슐 컴포넌트 클래스 선언
class USkeletalMeshComponent; // 스켈레탈 메시 컴포넌트 클래스 선언
class UInputMappingContext; // 입력 매핑 컨텍스트 클래스 선언
class UInputAction; // 입력 액션 클래스 선언
class USpringArmComponent; // 스프링 암 컴포넌트 클래스 선언
class UCameraComponent; // 카메라 컴포넌트 클래스 선언
UCLASS()
class UNREALSTUDY_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);

	// 입력 매핑 컨텍스트 선언
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* BirdMappingContext;

	// 입력 액션 선언
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MovedAction;

	// 카메라 움직임 입력 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	// 회전 입력 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RotateAction;

	// 입력 액션에 대한 처리 함수 선언
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);

private:
	// 캡슐 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	// 스켈레탈 메시 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	// 스프링 암 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom; // 스프링 암 컴포넌트 선언
	
	// 카메라 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera; // 카메라 컴포넌트 선언
};
