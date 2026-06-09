// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h" // 캡슐 컴포넌트 헤더 추가
#include "Components/SkeletalMeshComponent.h" // 스켈레탈 메시 컴포넌트 헤더 추가
#include "EnhancedInputComponent.h" // 향상된 입력 컴포넌트 헤더 추가
#include "EnhancedInputSubsystems.h" // 향상된 입력 서브시스템 헤더 추가
#include "GameFramework/PlayerController.h" // 플레이어 컨트롤러 헤더 추가
#include "Camera/CameraComponent.h" // 카메라 컴포넌트 헤더 추가
#include "GameFramework/SpringArmComponent.h" // 스프링 암 컴포넌트 헤더 추가

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

	// 스프링 암 컴포넌트 생성 및 캡슐 컴포넌트에 부착
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f; // 카메라와의 거리 설정
	CameraBoom->bUsePawnControlRotation = true; // 폰의 회전에 따라 스프링 암이 회전하도록 설정

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 스프링 암에 카메라 부착


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
	if(Controller != nullptr && (Value != 0.0f))
	{
		// 앞으로 이동하는 로직
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

// 입력 액션에 대한 처리 함수 구현
void ABird::Move(const FInputActionValue& Value)
{
	// 입력 액션에서 float 값을 가져와서 이동에 사용
	const float MovementValue = Value.Get<float>();
	if (Controller != nullptr && MovementValue != 0.0f)
    {
        // 폰의 앞쪽 방향 벡터
        FVector Forward = GetActorForwardVector();
        
        // 이동 컴포넌트에게 해당 방향으로 움직이라고 명령
        AddMovementInput(Forward, MovementValue);
    }
	
	// 로그 출력을 통해 입력이 제대로 처리되고 있는지 확인
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Move Action Triggered: %s"), *Value.ToString());
	}
}

// Look 액션에 대한 처리 함수 구현
void ABird::Look(const FInputActionValue& Value)
{
	// 입력 액션에서 FVector2D 값을 가져와서 카메라 회전에 사용
	const FVector2D LookValue = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// 카메라 회전을 위한 로직
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
	
	// 로그 출력을 통해 입력이 제대로 처리되고 있는지 확인
	if (!LookValue.IsZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Action Triggered: %s"), *Value.ToString());
	}
	
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 디버깅용 로그: 마우스를 움직일 때 이 두 값이 변해야 합니다!
    if (Controller != nullptr)
    {
        // 1. 플레이어 컨트롤러의 현재 회전값
        FString ControllerRot = Controller->GetControlRotation().ToString();
        // 2. 스프링암의 현재 회전값
        FString SpringArmRot = CameraBoom->GetComponentRotation().ToString();

        // 화면 왼쪽 위에 출력 (색상, 지속시간, 출력내용)
        GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Green, FString::Printf(TEXT("Controller Rot: %s"), *ControllerRot));
        GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::Yellow, FString::Printf(TEXT("SpringArm Rot: %s"), *SpringArmRot));
    }

}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 향상된 입력 시스템을 사용하여 입력 액션과 처리 함수를 바인딩
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 입력 액션과 처리 함수를 바인딩하여 입력을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(MovedAction, ETriggerEvent::Triggered, this, &ABird::Move);
		// Look 액션과 처리 함수를 바인딩하여 카메라 회전을 처리할 수 있도록 설정
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);
	}
	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
}

