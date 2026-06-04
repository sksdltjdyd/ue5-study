// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// 출력 로그 사용
	UE_LOG(LogTemp, Warning, TEXT("Beging Play Called!"));

	// 디버그 메시지 사용
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Red, TEXT("Beging Play Called!"));
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 매프레임마다 텍스트 발생
	UE_LOG(LogTemp, Warning, TEXT("Delta Time: %f"), DeltaTime);

	// 매 프레임마다 디버그 메시지 사용
	if (GEngine)
	{
		FString Name = GetName();
		FString Message = FString::Printf(TEXT("Item Name: %s, Delta Time: %f"), *Name, DeltaTime);
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Red, *Message);
		UE_LOG(LogTemp, Warning, TEXT("Item Name: %s, Delta Time: %f"), *Name, DeltaTime);
	}
}

