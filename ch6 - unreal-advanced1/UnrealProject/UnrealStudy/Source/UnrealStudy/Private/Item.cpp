// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UnrealStudy/DebugMacros.h"

// Sets default values
AItem::AItem() 
{
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject는 액터의 구성 요소를 생성하는 함수로, 템플릿 형태로 사용되어 UStaticMeshComponent 타입의 ItemMesh를 생성
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh; // 생성된 ItemMesh를 액터의 루트 컴포넌트로 설정
	
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	/*debug 메시지와 로그 예시
	
	// 출력 로그 사용
	UE_LOG(LogTemp, Warning, TEXT("Beging Play Called!"));

	// 디버그 메시지 사용
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Red, TEXT("Beging Play Called!"));
	}
	*/

	// GetWorld()는 AActor에서 제공하는 함수로, 현재 액터가 속한 월드에 대한 포인터를 반환
	

	// 액터 위치 변경
	// SetActorLocation(FVector(0.f, 0.f, 60.f));
	// 액터 회전 변경
	// SetActorRotation(FRotator(0.f, 45.f, 0.f));
	
	/*
	int32 AvgInt = Avg<int32>(10, 20); // 템플릿 함수 예시
	UE_LOG(LogTemp, Warning, TEXT("Average of 10 and 20 is: %d"), AvgInt);

	float AvgFloat = Avg<float>(10.f, 20.f);
	UE_LOG(LogTemp, Warning, TEXT("Average of 10.0 and 20.0 is: %f"), AvgFloat);
	*/
	
	// 디버그 라인 그리기
	// DRAW_LINE(Location, Location + Forward * 100.f, Color);

	// 디버그 구체 그리기
	// DRAW_SPHERE(Location, Color);

	// 디버그 포인트 그리기
	// DRAW_POINT(Location + Forward * 100.f, Color);

	// 디버그 벡터 그리기
	// DRAW_VECTOR(Location, Location + Forward * 100.f, Color);

	// 디버그 화살표 그리기
	// DRAW_ARROW(Location, Location + Forward * 100.f, Color);

	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FColor Color = FColor::Red;
}

float AItem::TransformSin(float Value)
{
	return FMath::Sin(Value * TimeConstant) * Amplitude;
}

float AItem::TransformRotation(float Value)
{
	return rotationSpeed * Value;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// cm/s 단위로 이동 속도 설정
	// float MoveSpeed = 50.f;
	// float rotationSpeed = 45.f; // degrees per second

	/*debug 메시지와 로그 예시
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
	*/
	
	// move speed * delta time cm/s * s/frame = cm/frame -> AddActorWorldOffset은 cm 단위로 위치를 변경하므로, MoveSpeed는 cm/s 단위로 설정
	// AddActorWorldOffset(FVector(MoveSpeed * DeltaTime, 0.f, 0.f));
	// AddActorWorldRotation(FRotator(0.f, rotationSpeed * DeltaTime, 0.f));

	//float DeltaZ = FMath::Sin(Value * TimeConstant) * Amplitude
	// float DeltaZ = TransformSin(RunningTime); // TimeConstant은 진동 주기를 조절하는 값, Amplitude는 진폭을 조절하는 값

	// AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
	// DRAW_SPHERE_SINGLE_FRAME(GetActorLocation(), FColor::Green);
	// DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f, FColor::Blue);

	// FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	// DRAW_POINT_SINGLE_FRAME(AvgVector, FColor::Yellow);

	RunningTime += DeltaTime;

	// 회전 변경
	AddActorWorldRotation(FRotator(0.f, rotationSpeed * DeltaTime, 0.f));
}

