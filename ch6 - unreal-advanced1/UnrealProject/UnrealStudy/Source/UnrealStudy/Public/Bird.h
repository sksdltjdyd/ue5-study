// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;

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

private:
	// 캡슐 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	// 스켈레탈 메시 컴포넌트 선언
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;
};
