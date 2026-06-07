// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class UNREALSTUDY_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	// 엔진 내 블루프린트에서 편집할 수 있도록 UPROPERTY 매크로를 사용하여 Amplitude와 TimeConstant 변수를 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties") // Blueprint에서도 편집할 수 있도록 BlueprintReadWrite로 설정
	float Amplitude = 0.25f;
	UPROPERTY(EditAnywhere, Category = "Item Properties")
	float TimeConstant = 5.f; // 진동 주기를 조절하는 값

	UPROPERTY(EditAnywhere, Category = "Item Properties")
	float rotationSpeed = 45.f; // 회전 속도를 조절하는 값

	UFUNCTION(BlueprintCallable, Category = "Item Functions")
	float TransformSin(float Value);

	UFUNCTION(BlueprintCallable, Category = "Item Functions")
	float TransformRotation(float Value);

	template<typename T>
	T Avg(T First, T Second);
private:
	// RunningTime은 액터가 시작된 이후로 경과된 시간을 추적하는 변수로 Tick 함수에서 DeltaTime을 더하여 업데이트
	// 블루프린트에서 편집할 필요가 없으므로 UPROPERTY 매크로를 사용하여 VisibleAnywhere로 설정
	// meta = (AllowPrivateAccess = "true")는 C++에서 private로 선언된 변수를 블루프린트에서 읽을 수 있도록 허용하는 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Properties") 
	float RunningTime;

	// ItemMesh는 아이템의 시각적 표현을 담당하는 UStaticMeshComponent로, VisibleAnywhere로 설정하여 블루프린트에서 읽을 수 있지만 편집은 불가능하도록 설정
	// Category는 "Item Properties"로 설정하여 블루프린트에서 관련 변수
	UPROPERTY(VisibleAnywhere, Category = "Item Properties")
	UStaticMeshComponent* ItemMesh;
};

template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}