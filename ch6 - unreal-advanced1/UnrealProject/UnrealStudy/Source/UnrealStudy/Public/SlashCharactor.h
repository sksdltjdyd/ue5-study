// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlashCharactor.generated.h"

UCLASS()
class UNREALSTUDY_API ASlashCharactor : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharactor();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

