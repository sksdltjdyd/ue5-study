// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h" // 캡슐 컴포넌트 헤더 추가
#include "Components/SkeletalMeshComponent.h" // 스켈레탈 메시 컴포넌트 헤더 추가
#include "EnhancedInputComponent.h" // 향상된 입력 컴포넌트 헤더 추가
#include "EnhancedInputSubsystems.h" // 향상된 입력 서브시스템 헤더 추가
#include "GameFramework/PlayerController.h" // 플레이어 컨트롤러 헤더 추가

// Sets default values
ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캡슐 컴포넌트 생성 및 루트 컴포넌트로 설정
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	// 스켈레탈 메시 컴포넌트 생성 및 캡슐 컴포넌트에 부착
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 플레이어 입력 자동 수신 설정
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	// 입력 매핑 컨텍스트가 설정되어 있는지 확인
	// 플레이어 컨트롤러를 가져와서 입력 매핑 컨텍스트를 추가
	if (APlayerController* UnrealStudyPlayerController = Cast<APlayerController>(GetController()))
	{
		// 입력 매핑 컨텍스트를 플레이어 컨트롤러에 추가
		// UEnhancedInputLocalPlayerSubsystem을 사용하여 입력 매핑 컨텍스트를 추가
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(UnrealStudyPlayerController->GetLocalPlayer()))
		{
			// 입력 매핑 컨텍스트를 추가하여 입력을 처리할 수 있도록 설정
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}		
	}
}

void ABird::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value);
}

// 입력 액션에 대한 처리 함수 구현
void ABird::Move(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Move Action Triggered: %s"), *Value.ToString());
	}
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 향상된 입력 시스템을 사용하여 입력 액션과 처리 함수를 바인딩
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 입력 액션과 처리 함수를 바인딩하여 입력을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(MovedAction, ETriggerEvent::Triggered, this, &ABird::Move);
	}

	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
}

